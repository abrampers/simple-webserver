#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uv.h>

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

uv_loop_t *loop;

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

class HttpWebserver {
    std::string method;
    std::string url;
    std::string version;

    std::map<std::string, std::string> headers;

public:

    HttpWebserver(char *request) {
        std::string str(request);
        std::stringstream ss(str);
        std::string line, ignore;

        std::getline(ss, line, '\r');
        std::getline(ss, ignore, '\n');
        
        this->on_read_request_line(line);
    }

    std::string get_response() {
        std::stringstream ssOut;
        std::string file_path;
        bool url_valid = false;
        
        if (url == "/" || url == "/5.html") {
            file_path = "../public/5.html";
            url_valid = true;
        } else if (url == "/20.html") {
            file_path = "../public/20.html";
            url_valid = true;
        }

        if(url_valid) {
            std::string sHTML, temp;
            std::ifstream stream;

            stream.open(file_path, std::ios::in);
            while(stream >> temp) {
                sHTML += temp;
            }
            //  stream >> sHTML;
            stream.close();

            ssOut << "HTTP/1.1 200 OK" << std::endl;
            ssOut << "content-type: text/html" << std::endl;
            ssOut << "content-length: " << sHTML.length() << std::endl;
            ssOut << std::endl;
            ssOut << sHTML;
        } else {
            std::string sHTML = "<html><body><h1>404 Not Found</h1><p>There's nothing here.</p></body></html>";
            ssOut << "HTTP/1.1 404 Not Found" << std::endl;
            ssOut << "content-type: text/html" << std::endl;
            ssOut << "content-length: " << sHTML.length() << std::endl;
            ssOut << std::endl;
            ssOut << sHTML;
        }
        return ssOut.str();
    }

    int content_length() {
        auto request = headers.find("content-length");
        if(request != headers.end()) {
            std::stringstream ssLength(request->second);
            int content_length;
            ssLength >> content_length;
            return content_length;
        }
        return 0;
    }

    void on_read_header(std::string line) {   
        std::stringstream ssHeader(line);
        std::string headerName;
        std::getline(ssHeader, headerName, ':');

        std::string value;
        std::getline(ssHeader, value);
        headers[headerName] = value;
    }

    void on_read_request_line(std::string line) {
        std::stringstream ssRequestLine(line);
        ssRequestLine >> method;
        ssRequestLine >> url;
        ssRequestLine >> version;

        printf("request for resource: %s\n", url.c_str());
    }
};

uv_buf_t build_response(uv_buf_t buf) {
    printf("LEN: %zu\n", buf.len);
    printf("\n");
    printf("BUFFER\n");
    printf("%s\n", buf.base);

    HttpWebserver ws(buf.base);

    std::string res = ws.get_response();
    char *base = (char *) res.c_str();
    unsigned int len = (unsigned int) res.length();

    printf("res\n\n%s\n", base);

    return uv_buf_init(base, len);
}

void free_write_req(uv_write_t *req) {
    write_req_t *wr = (write_req_t*) req;
    free(wr->buf.base);
    free(wr);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}

void echo_write(uv_write_t *req, int status) {
    if (status) {
        fprintf(stderr, "Write error %s\n", uv_strerror(status));
    }
    free_write_req(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    if (nread > 0) {
        write_req_t *req = (write_req_t*) malloc(sizeof(write_req_t));
        req->buf = uv_buf_init(buf->base, nread);
        uv_buf_t response_buf = build_response(req->buf);

        uv_write((uv_write_t*) req, client, &response_buf, 1, echo_write);
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            fprintf(stderr, "Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, NULL);
    }

    free(buf->base);
}

void on_new_connection(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "New connection error %s\n", uv_strerror(status));
        // error!
        return;
    }

    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);
    if (uv_accept(server, (uv_stream_t*) client) == 0) {
        uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
    } else {
        uv_close((uv_handle_t*) client, NULL);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./simple-webserver <PORT>\n");
        return 1;
    }

    const int PORT = atoi(argv[1]);
    const int DEFAULT_BACKLOG = 128;
    uv_tcp_t server;
    struct sockaddr_in addr;

    loop = uv_default_loop();
    uv_tcp_init(loop, &server);

    uv_ip4_addr("0.0.0.0", PORT, &addr);

    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);
    int r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);
    // printf("Listening on port %d", PORT);
    if (r) {
        fprintf(stderr, "Listen error %s\n", uv_strerror(r));
        return 1;
    }
    return uv_run(loop, UV_RUN_DEFAULT);
}
