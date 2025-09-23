cmake_minimum_required(VERSION 3.10)

project(viper VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OUTPUT_BIN_DIR ${CMAKE_BINARY_DIR}/bin)
set(OUTPUT_LIB_DIR ${CMAKE_BINARY_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_INSTALL_PREFIX "/usr/local/os-artificer/viper")
set(CMAKE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_PREFIX}/include")
set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_BINDIR "${CMAKE_INSTALL_PREFIX}/bin")

# load custom modules
# set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# find_package()

option(BUILD_DEPENDENCIES "Build denpendencies" OFF)
option(BUILD_TESTS "Build test cases" OFF)

string(TIMESTAMP BUILT_TIME "%Y-%m-%d %H:%M:%S")

execute_process(
    COMMAND git rev-parse --short HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_ID
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(NOT DEFINED VERSION)
    set(VERSION "unknown")
endif()

include_directories(${CMAKE_SOURCE_DIR}/src
                    ${CMAKE_SOURCE_DIR}/include)

include_directories(/usr/lib
                    /usr/local/include)

link_directories(/usr/lib
                /usr/lib64
                /usr/local/lib
                /usr/local/lib64)

add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(viper-tool)

# Install public headers
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT dev)

# Install libs
install(TARGETS viper
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT runtime
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}" COMPONENT dev)

# Install bins
install(TARGETS viper-tool
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT runtime)
