cmake_minimum_required(VERSION 3.14)
project(bendio)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/impl)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(bendio STATIC ${SRC_FILES})
target_include_directories(bendio PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(bendio PUBLIC ${PROJECT_SOURCE_DIR}/impl)

add_executable(myapp main.cpp)
target_link_libraries(myapp PRIVATE bendio)

### You can want to use: ###
#
# add_subdirectory(cpp-bendio EXCLUDE_FROM_ALL)
# target_link_libraries(my_other_target PRIVATE bendio)
