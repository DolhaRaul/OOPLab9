//
// Created by rauld on 09.05.2022.
//

#include "UI.h"
UI::UI() {}
UI::UI(Service &service)
{
    this->sv = service;
}
UI::~UI(){}
void UI::show_menu()
{
    cout << "add.Adaugare booking" << endl;
    cout << "del.Stergere booking" << endl;
    cout << "update.Modificare booking" << endl;
    cout << "cautare_hotel.Afisam toate booking urile ce au un nume dorit" << endl;
    cout << "cautare_hotel_oras_perioada.Afisam toate booking urile ce au hotelul in orasul dorit si are rezervare";
    cout <<  " disponibila in perioada dorita, sau eventual in perioade sugerate la interval de +-3zile distanta" << endl;
    cout << "number.Afisam numarul total de booking uri" << endl;
    cout << "show_all.Booking urile curente" << endl;
    cout << "0.Iesire" << endl;
}
void UI::show_all()
{
    for(int i = 0; i < this->sv.get_nr_elem(); i++)
        cout << "Booking ul al " << i + 1 << " este:" << endl << this->sv.get_elems()[i];
}
void UI::numar_entitati()
{
    cout << "Numarul de entitati este: " << this->sv.get_nr_elem() << endl;
}
void UI::adaugare()
{
    Booking b;
    cin >> b;
    int rez = this->sv.add(b.get_cod(), b.get_nume(), b.get_oras(), b.get_data_inc(), b.get_data_sf());
    if(rez)
        cout << "Booking ul a fost adaugat cu succes!" << endl;
    else
        cout << "Booking ul nu a putut fi adaugat!" << endl;
}
void UI::stergere()
{
    cout << "Introduceti codul Booking ului ce doreste a fi sters aici: ";
    int cod;
    cin >> cod;
    cout << endl;
    int rez = this->sv.del(cod);
    if(rez)
        cout << "Booking ul a fost sters cu succes!" << endl;
    else
        cout << "Booking ul nu a putut fi sters!" << endl;
}
void UI::modificare()
{
    Booking b;
    cin >> b;
    int rez = this->sv.modify(b.get_cod(), b.get_nume(), b.get_oras(), b.get_data_inc(), b.get_data_sf());
    if(rez)
        cout << "Booking ul a fost modificat!" << endl;
    else
        cout << "Booking ul nu a putut fi modificat!" << endl;
}
void UI::cautare_hotele()
{
    char* oras = new char[30];
    cout << "Introduceti orasul hotelului pentru care cautam booking uri:" << endl;
    cin >> oras;
    vector<Booking> hotele = this->sv.search_after_oras(oras);
    if(hotele.capacity() == 0)
        cout << "Nu avem booking uri pentru acest nume de hotel!" << endl;
    else
        for(int i = 0; i < hotele.size(); i++)
            cout << "Booking ul al " << i + 1 << " lea este: " << endl << hotele.at(i);
    delete[] oras;
}
void UI::cautare_hotele_oras_perioada()
{
    char* oras = new char[30];
    cout << "Introduceti numele orasului pentru care cautam hoteluri uri:" << endl;
    cin >> oras;
    Data begin;
    Data end;
    cout << "Dati perioada de inceput a croazierei aici:" << endl;
    cin >> begin;
    cout << "Dati finalul perioadei de croaziera aici:" << endl;
    cin >> end;
    this->sv.search_booking_oras_perioada(oras, begin, end);
}
void UI::run_menu()
{
    string optiune;
    while(optiune != "0")
    {
        if(optiune == "add")
            UI::adaugare();
        if(optiune == "del")
            UI::stergere();
        if(optiune == "update")
            UI::modificare();
        if(optiune == "cautare_hotel")
            UI::cautare_hotele();
        if(optiune == "cautare_hotel_oras_perioada")
            UI::cautare_hotele_oras_perioada();
        if(optiune == "number")
            UI::numar_entitati();
        if(optiune == "show_all")
            UI::show_all();
        UI::show_menu();
        cout << "Introduceti optiunea dorita aici:" << endl;
        cin >> optiune;
    }
}