cmake_minimum_required (VERSION 2.6)
set (CMAKE_CXX_STANDARD 11)
project (simple-webserver)
set(APP_TARGET simple-webserver)

#  Boost
set(BOOST_ROOT lib/boost)
find_package(Boost 1.70.0 REQUIRED system)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

add_executable(${APP_TARGET} main.cpp)
target_link_libraries(
        ${APP_TARGET}
        ${Boost_SYSTEM_LIBRARY}
)
