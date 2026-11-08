cmake_minimum_required(VERSION 4.0)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP ON
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE) #предотвращает конфликты между библиотеками времени выполнения, которые могут возникнуть при линковке программы и GTest.

FetchContent_MakeAvailable(googletest)

include_directories(${googletest_SOURCE_DIR}/googletest/include)
include_directories(${googletest_SOURCE_DIR}/googlemock/include)

add_executable(lab2 main.cpp
        Trie.h
        Trie.cpp
        Node.h
)

enable_testing()

add_executable(trie_tests tests_trie.cpp
        Trie.h
        Trie.cpp
        Node.h
)

target_link_libraries(
        trie_tests
        PRIVATE
        GTest::gtest_main # Предоставляет функцию main() для тестов
)

include(GoogleTest)
gtest_discover_tests(trie_tests)
