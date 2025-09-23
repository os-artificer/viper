project(viper-tool)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BIN_DIR})

message("example Output Dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

list(FILTER SOURCES EXCLUDE REGEX "test")

add_executable(${PROJECT_NAME} ${SOURCES})

list(APPEND LIBS viper)

# set macros
target_compile_definitions(${PROJECT_NAME} PRIVATE "VERSION=\"${VERSION}\"")                                                                             
target_compile_definitions(${PROJECT_NAME} PRIVATE "GIT_COMMIT_ID=\"${GIT_COMMIT_ID}\"")  

# link libs
target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})
