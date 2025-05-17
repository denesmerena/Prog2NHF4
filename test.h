#ifndef TEST_H
#define TEST_H

#include "menu.h"
#include "gtest_lite.h"
#include "memtrace.h"

class MenuTest {
public:
    static void testClearInputBuffer();
    static void testUjAlapanyagBevitel();
    static void testUjReceptBevitel();
    static void testReceptTorles();
    static void testHozzavalokListazasa();
    static void testAdatbazisMentesBetoltes();

    static void runAllTests();
};

#endif // TEST_H