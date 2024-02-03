cmake_minimum_required(VERSION 3.5)
project(rsa LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(rsacrypt
        rsacrypt.cpp
        rsa.cpp
        rsa_decryptor.cpp
        rsa_encryptor.cpp
        controller.cpp
        helper.cpp
        menu.cpp
        prime_candidate.cpp
        rsa.h
        rsa_decryptor.h
        rsa_encryptor.h
        controller.h
        helper.h
        menu.h
        prime_candidate.h
)

if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU" )
    target_compile_options( rsacrypt PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
    target_compile_options( rsacrypt PRIVATE /W4 )
endif()