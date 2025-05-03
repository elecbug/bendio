cmake_minimum_required(VERSION 3.14)
project(bendio)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/public_include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/impl)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

add_library(bendio STATIC ${SRC_FILES})
target_include_directories(bendio PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/public_include> $<INSTALL_INTERFACE:include>)
target_include_directories(bendio PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(bendio PRIVATE ${PROJECT_SOURCE_DIR}/impl)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE bendio)

# Install library target
install(TARGETS bendio EXPORT bendioTargets ARCHIVE DESTINATION lib INCLUDES DESTINATION include)

# Install public headers
install(DIRECTORY public_include/ DESTINATION include)

# Export the targets to a file
install(EXPORT bendioTargets FILE bendioTargets.cmake NAMESPACE bendio:: DESTINATION lib/cmake/bendio)

# Create a basic Config file for find_package
include(CMakePackageConfigHelpers)

write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/bendioConfigVersion.cmake" VERSION 1.0.0 COMPATIBILITY AnyNewerVersion)

configure_package_config_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/bendioConfig.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/bendioConfig.cmake" INSTALL_DESTINATION lib/cmake/bendio)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/bendioConfig.cmake" "${CMAKE_CURRENT_BINARY_DIR}/bendioConfigVersion.cmake" DESTINATION lib/cmake/bendio)
