cmake_minimum_required(VERSION 3.31)
project(Prog2NHF4)

set(CMAKE_CXX_STANDARD 20)

add_executable(NHF
        main.cpp

hozzavalo.h
recept.h
        alapanyag.cpp
        hozzavalo.cpp
        recept.cpp
        tarolo.h
        tarolo.cpp

alapanyag.h
        menu.h
        menu.cpp
test.cpp
        gtest_lite.h
memtrace.h
memtrace.cpp
        test.h
        fajlkezelo.cpp
        fajlkezelo.h)

add_compile_definitions(MEMTRACE)
