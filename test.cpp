#include "alapanyag.h"
#include "recept.h"
#include "tarolo.h"
#include "fajlkezelo.h"

#include "gtest_lite.h"
#include "memtrace.h"

#include <cstdio>  // std::remove

void test_Alapanyag_es_Tarolo() {
    TEST(Functional, AlapanyagTarolas) {
        Tarolo<Alapanyag> alapanyagTarolo;

        Alapanyag* viz = new Alapanyag("Viz", "ml");
        Alapanyag* cukor = new Alapanyag("Cukor", "g");

        alapanyagTarolo.add(viz);
        alapanyagTarolo.add(cukor);

        EXPECT_EQ(2, alapanyagTarolo.getMennyiseg());
        EXPECT_STREQ("Viz", alapanyagTarolo[0]->getNev().c_str());
        EXPECT_STREQ("Cukor", alapanyagTarolo[1]->getNev().c_str());
    } END
}

void test_Recept_es_Hozzavalo() {
    TEST(Functional, ReceptLetrehozas) {
        Tarolo<Alapanyag> alapanyagTarolo;
        alapanyagTarolo.add(new Alapanyag("Viz", "ml"));
        alapanyagTarolo.add(new Alapanyag("Cukor", "g"));

        Recept* recept = new Recept("Cukros víz");
        recept->hozzavalohozzaad(*alapanyagTarolo[0], 200);
        recept->hozzavalohozzaad(*alapanyagTarolo[1], 15);

        EXPECT_STREQ("Cukros víz", recept->getNev().c_str());
        EXPECT_EQ(2, recept->getHozzavaloCount());
        EXPECT_STREQ("Viz", recept->getHozzavalo(0)->getAlapanyag().getNev().c_str());

        delete recept; // mivel nem tároltuk Tarolóban
    } END
}

void test_Mentes_es_Betoltes() {
    TEST(Functional, FajlMentesBetoltes) {
        const char* fajlnev = "teszt_recept.txt";

        // --- Adatok létrehozása ---
        Tarolo<Alapanyag> alapanyagTarolo;
        Tarolo<Recept> receptTarolo;

        Alapanyag* citrom = new Alapanyag("Citromle", "ml");
        Alapanyag* cukor = new Alapanyag("Cukor", "g");
        alapanyagTarolo.add(citrom);
        alapanyagTarolo.add(cukor);

        Recept* limonade = new Recept("Limonade");
        limonade->hozzavalohozzaad(*citrom, 50);
        limonade->hozzavalohozzaad(*cukor, 10);
        receptTarolo.add(limonade);

        // --- Mentés fájlba ---
        Fajlkezelo::mentes(receptTarolo, alapanyagTarolo, fajlnev);

        // --- Betöltés új példányba ---
        Tarolo<Alapanyag> beAlapanyagok;
        Tarolo<Recept> beReceptek;
        Fajlkezelo::betoltes(beReceptek, beAlapanyagok, fajlnev);

        // --- Ellenőrzés ---
        EXPECT_EQ(2, beAlapanyagok.getMennyiseg());
        EXPECT_EQ(1, beReceptek.getMennyiseg());

        const Recept* betoltott = beReceptek[0];
        EXPECT_STREQ("Limonade", betoltott->getNev().c_str());
        EXPECT_EQ(2, betoltott->getHozzavaloCount());

        const Hozzavalo* h0 = betoltott->getHozzavalo(0);
        const Hozzavalo* h1 = betoltott->getHozzavalo(1);

        // Ellenőrzés sorrendfüggetlenül
        EXPECT_TRUE(
            (h0->getAlapanyag().getNev() == "Citromle" && h0->getMennyiseg() == 50) ||
            (h1->getAlapanyag().getNev() == "Citromle" && h1->getMennyiseg() == 50)
        );

        EXPECT_TRUE(
            (h0->getAlapanyag().getNev() == "Cukor" && h0->getMennyiseg() == 10) ||
            (h1->getAlapanyag().getNev() == "Cukor" && h1->getMennyiseg() == 10)
        );

        std::remove(fajlnev);
    } END
}

