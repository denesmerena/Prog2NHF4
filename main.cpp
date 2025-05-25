#ifdef CPORTA
#include "test.h"
int main() {
    test_Alapanyag_es_Tarolo();
    test_Recept_es_Hozzavalo();
    test_Mentes_es_Betoltes();
    return 0;
}
#else
#include "menu.h"
int main() {
    Tarolo<Alapanyag> alapanyagTarolo;
    Tarolo<Recept> receptTarolo;
    Menu menu(alapanyagTarolo, receptTarolo);
    menu.run();
    return 0;
}
#endif

