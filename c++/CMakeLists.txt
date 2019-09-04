cmake_minimum_required (VERSION 2.8.12)
set(CMAKE_CXX_STANDARD 11)
project(simple-webserver)
set(APP_TARGET simple-webserver)

# libuv
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
find_package(libuv REQUIRED)

add_executable(${APP_TARGET} src/main.cc)
target_include_directories(${APP_TARGET} PRIVATE ${LIBUV_INCLUDE_DIRS})
target_link_libraries(${APP_TARGET} ${LIBUV_LIBRARIES})