#include <iostream>
#include "Teste.h"
#include "Booking.h"
#include "Repository.h"
#include "Service.h"
#include "UI.h"
using namespace std;

int main() {
    Teste::teste_entitate();
    Teste::teste_repository_live();
    Teste::teste_repository_tema();
    Teste::teste_repository_file();
    Teste::teste_operatori_data();
    Teste::teste_service_tema();
    ///RepositoryInFile r("Booking.txt");
    Repository r;
    Service sv(r);
    UI ui(sv);
    ui.run_menu();

    return 0;
}
