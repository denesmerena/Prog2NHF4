#include "test.h"
#include "fajlkezelo.h"
#include <stdio.h>
#include <sstream>

// void MenuTest::testClearInputBuffer() {
//     Tarolo<Alapanyag> alapanyagTarolo;
//     Tarolo<Recept> receptTarolo;
//     Menu menu(alapanyagTarolo, receptTarolo);
//
//     TEST(MenuTest, ClearInputBuffer) {
//         // Simulate bad input
//         std::istringstream input("bad\ninput\n");
//         std::cin.rdbuf(input.rdbuf());
//
//         menu.clearInputBuffer();
//
//         // Verify buffer is cleared
//         char c;
//         std::cin >> c;
//         EXPECT_TRUE(std::cin.eof() || std::cin.fail());
//
//         std::cin.clear();
//     } END
// }

void MenuTest::testUjAlapanyagBevitel() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;
    Menu menu(alapanyagTarolo, receptTarolo);

    TEST(MenuTest, UjAlapanyagBevitel) {
        std::istringstream input("TesztAlapanyag\ng\n");
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

        menu.ujAlapanyagBevitel();

        std::cin.rdbuf(oldCin);

        EXPECT_EQ(1, alapanyagTarolo.getMennyiseg());
        EXPECT_STREQ("TesztAlapanyag", (*alapanyagTarolo[0]).getNev().c_str());
        EXPECT_STREQ("g", (*alapanyagTarolo[0]).getMertekegyseg().c_str());
    } END
}

void MenuTest::testUjReceptBevitel() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;

    // First add an ingredient
    alapanyagTarolo.add(new Alapanyag("Viz", "ml"));

    Menu menu(alapanyagTarolo, receptTarolo);

    TEST(MenuTest, UjReceptBevitel) {
        std::istringstream input("Limonade\n1\n300\nn\n");
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

        menu.ujReceptBevitel();

        std::cin.rdbuf(oldCin);

        EXPECT_EQ(1, receptTarolo.getMennyiseg());
        EXPECT_STREQ("Limonade", (*receptTarolo[0]).getNev().c_str());
        EXPECT_EQ(1, (*receptTarolo[0]).getHozzavaloCount());
    } END
}

void MenuTest::testReceptTorles() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;

    // Add a test recipe
    receptTarolo.add(new Recept("Test Recept"));

    Menu menu(alapanyagTarolo, receptTarolo);

    TEST(MenuTest, ReceptTorles) {
        std::istringstream input("1\n");
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

        size_t originalCount = receptTarolo.getMennyiseg();
        menu.receptTorles();

        std::cin.rdbuf(oldCin);

        EXPECT_EQ(originalCount - 1, receptTarolo.getMennyiseg());
    } END
}

void MenuTest::testHozzavalokListazasa() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;

    // Add test data
    Alapanyag* viz = new Alapanyag("Viz", "ml");
    alapanyagTarolo.add(viz);

    Recept* recept = new Recept("Test Recept");
    recept->hozzavalohozzaad(*viz, 300);
    receptTarolo.add(recept);

    Menu menu(alapanyagTarolo, receptTarolo);

    TEST(MenuTest, HozzavalokListazasa) {
        std::istringstream input("1\n");
        std::streambuf* oldCin = std::cin.rdbuf(input.rdbuf());

        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        menu.hozzavalokListazasa();

        std::cout.rdbuf(oldCout);
        std::cin.rdbuf(oldCin);

        std::string result = output.str();
        EXPECT_NE(std::string::npos, result.find("Test Recept recept hozzávalói:"));
        EXPECT_NE(std::string::npos, result.find("- Viz: 300 ml"));
    } END
}

void MenuTest::testAdatbazisMentesBetoltes() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;

    // Add test data
    Alapanyag* viz = new Alapanyag("Viz", "ml");
    alapanyagTarolo.add(viz);

    Recept* recept = new Recept("Test Recept");
    recept->hozzavalohozzaad(*viz, 300);
    receptTarolo.add(recept);

    Menu menu(alapanyagTarolo, receptTarolo);

    TEST(MenuTest, AdatbazisMentesBetoltes) {
        // Test save
        std::string testFile = "test_db.txt";
        std::remove(testFile.c_str()); // Delete if exists

        // Save
        Fajlkezelo::mentes(receptTarolo, alapanyagTarolo, testFile);

        // Create new containers for loading
        Tarolo<Alapanyag> loadedAlapanyagok;
        Tarolo<Recept> loadedReceptek;

        // Load
        Fajlkezelo::betoltes(loadedReceptek, loadedAlapanyagok, testFile);

        // Verify
        EXPECT_EQ(1, loadedAlapanyagok.getMennyiseg());
        EXPECT_EQ(1, loadedReceptek.getMennyiseg());
        EXPECT_STREQ("Test Recept", (*loadedReceptek[0]).getNev().c_str());

        std::remove(testFile.c_str()); // Clean up
    } END
}

// Update runAllTests to include new tests
void MenuTest::runAllTests() {
    //testClearInputBuffer();
    testUjAlapanyagBevitel();
    testUjReceptBevitel();
    testReceptTorles();
    testHozzavalokListazasa();
    testAdatbazisMentesBetoltes();

    TEST(MenuTest, DisplayMenu) {
        Tarolo<Alapanyag> alapanyagTarolo;
        Tarolo<Recept> receptTarolo;
        Menu menu(alapanyagTarolo, receptTarolo);

        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

        menu.displayMenu();

        std::cout.rdbuf(oldCout);

        std::string result = output.str();
        EXPECT_NE(std::string::npos, result.find("Italrecept Nyilvántartó"));
        EXPECT_NE(std::string::npos, result.find("Új alapanyag bevitele"));
    } END

    TEST(MenuTest, PublicInterface) {
        Tarolo<Alapanyag> alapanyagTarolo;
        Tarolo<Recept> receptTarolo;
        Menu menu(alapanyagTarolo, receptTarolo);

        SUCCEED();
    } ENDM
}

