cmake_minimum_required(VERSION 4.0)
project(lab_intro)

set(CMAKE_CXX_STANDARD 20)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

add_executable(lab_intro main.cpp
        WordCounter.h
        WordCounter.cpp
        TextReader.h
        CsvWriter.cpp
        CsvWriter.h
        Word.h)

if(MINGW)
    target_link_options(lab_intro PRIVATE
            -static-libgcc
            -static-libstdc++
            -static
    )
endif()