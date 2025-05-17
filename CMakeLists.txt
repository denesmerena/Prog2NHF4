cmake_minimum_required(VERSION 3.31)
project(Prog2NHF4)

set(CMAKE_CXX_STANDARD 20)

add_executable(NHF
        main.cpp
        fajlkezelo.h
hozzavalo.h
recept.h
        alapanyag.cpp
        hozzavalo.cpp
        recept.cpp
        tarolo.h
        tarolo.cpp
        fajlkezelo.cpp
alapanyag.h
        menu.h
        menu.cpp
test.cpp
test.h
gtest_lite.h
memtrace.h
memtrace.cpp)

add_compile_definitions(MEMTRACE)
