cmake_minimum_required(VERSION 3.14)
project(MyTcpSdk)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB_RECURSE ALL_SRC CONFIGURE_DEPENDS "src/*.cpp")
add_executable(myapp main.cpp ${ALL_SRC})
