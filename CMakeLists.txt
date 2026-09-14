cmake_minimum_required(VERSION 4.4)
project(string2.h)

set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_BUILD_TYPE Debug)

add_library(string2.h)
target_sources(string2.h
    PRIVATE
        src/main/string2.c
        src/main/string2_builder.c
    PUBLIC
    FILE_SET string2header
    TYPE HEADERS
    BASE_DIRS include
    FILES include/string2.h/string2.h
)

# Tests
add_executable(strreadtest src/test/stringreadtest.c)
add_executable(filereader src/test/filereader.c)
target_link_libraries(strreadtest string2.h)
target_link_libraries(filereader string2.h)