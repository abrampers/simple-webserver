# simple-webserver

## C++
### Dependencies
1. libuv
You have to make sure CMake can find libuv library
```sh-session
brew install libuv
```

### Building
#### C++
```sh-session
cd c++
mkdir build
cd build
cmake ..
make
```

### Running the webserver
```sh-session
cd build
./simple-webserver <PORT>
```

#### Node.js
```sh-session
```