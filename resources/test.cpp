#include "alapanyag.h"
#include "recept.h"
#include "tarolo.h"
#include "fajlkezelo.h"

#include "gtest_lite.h"
#include "memtrace.h"

#include <cstdio>
#include <sstream>

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

        Tarolo<Alapanyag> uresTarolo;

        for (int i = 0; i < 15; ++i) {
            uresTarolo.add(new Alapanyag("Anyag" + std::to_string(i), "egység"));
        }

        EXPECT_EQ(15, uresTarolo.getMennyiseg());
        EXPECT_STREQ("Anyag0", uresTarolo[0]->getNev().c_str());
        EXPECT_STREQ("Anyag14", uresTarolo[14]->getNev().c_str());


    } END
    TEST(Functional, TaroloRemove) {
        Tarolo<Alapanyag> tarolo;
        tarolo.add(new Alapanyag("A", "x"));
        tarolo.add(new Alapanyag("B", "y"));
        tarolo.add(new Alapanyag("C", "z"));

        EXPECT_EQ(3, tarolo.getMennyiseg());

        tarolo.remove(1); // távolítsuk el a "B"-t
        EXPECT_EQ(2, tarolo.getMennyiseg());
        EXPECT_STREQ("A", tarolo[0]->getNev().c_str());
        EXPECT_STREQ("C", tarolo[1]->getNev().c_str());
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
        EXPECT_STREQ("Viz", recept->operator[](0)->getAlapanyag().getNev().c_str());
        Alapanyag viz("Viz", "ml");
        Alapanyag cukor("Cukor", "g");

        std::ostringstream oss1;
        oss1 << viz;
        EXPECT_STREQ("Viz (ml)", oss1.str().c_str());

        Hozzavalo hozzavalo(cukor, 25);
        std::ostringstream oss2;
        oss2 << hozzavalo;
        EXPECT_STREQ("25 g Cukor", oss2.str().c_str());


        delete recept;
    } END
    TEST(Functional, ReceptResize) {
        Tarolo<Alapanyag> alapanyagTarolo;
        for (int i = 0; i < 20; ++i) {
            alapanyagTarolo.add(new Alapanyag("A" + std::to_string(i), "ml"));
        }

        Recept* recept = new Recept("NagyRecept");
        for (int i = 0; i < 20; ++i) {
            recept->hozzavalohozzaad(*alapanyagTarolo[i], i * 10);
        }

        EXPECT_EQ(20, recept->getHozzavaloCount());
        EXPECT_STREQ("A0", recept->operator[](0)->getAlapanyag().getNev().c_str());
        EXPECT_EQ(190, recept->operator[](19)->getMennyiseg());

        delete recept;
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

        const Hozzavalo* h0 = betoltott->operator[](0);
        const Hozzavalo* h1 = betoltott->operator[](1);

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

