cmake_minimum_required(VERSION 3.20)
project(cg)

set(CMAKE_CXX_STANDARD 14)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-D ENV_WIN)
ELSEIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_definitions(-D ENV_DARWIN)
ENDIF()

IF(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Debug"))
    add_definitions(-D __CMAKE_DEBUG__)
ELSEIF(CMAKE_BUILD_TYPE AND (CMAKE_BUILD_TYPE STREQUAL "Release"))
    add_definitions(-D __CMAKE_RELEASE__)
ENDIF()
add_executable(cg main.cpp opcode.h handler.cpp bug_message.h num_magic.cpp num_magic.h bit_sequence.h handler.h machine_code.cpp machine_code.h translator.cpp translator.h global_data.cpp assembly.cpp assembly.h operation_code.h operation_code.cpp token.cpp token.h init.cpp)
