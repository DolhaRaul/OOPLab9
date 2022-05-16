//
// Created by rauld on 09.05.2022.
//

#include "UI.h"
#include "Data.h"
///UI::UI() {}
UI::~UI(){}
void UI::show_menu()
{
    cout << "add.Adaugare booking" << endl;
    cout << "del.Stergere booking" << endl;
    cout << "update.Modificare booking" << endl;
    cout << "cautare_hotel.Afisam toate booking urile ce au un nume dorit" << endl;
    cout << "cautare_hotel_oras_perioada.Afisam toate booking urile ce au hotelul in orasul dorit si are rezervare" << endl;
    cout << "disponibila in perioada dorita, sau eventual in perioade sugerate la interval de +-3zile distanta" << endl;
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
    string oras;
    cout << "Introduceti orasul hotelului pentru care cautam booking uri:" << endl;
    cin >> oras;
    vector<Booking> hotele = this->sv.search_after_oras(oras);
    if(hotele.capacity() == 0)
        cout << "Nu avem booking uri pentru acest nume de hotel!" << endl;
    else
        for(int i = 0; i < hotele.size(); i++)
            cout << "Booking ul al " << i + 1 << " lea este: " << endl << hotele.at(i);
}
void UI::cautare_hotele_oras_perioada()
{
    string oras;
    cout << "Introduceti numele orasului pentru care cautam hoteluri uri:" << endl;
    cin >> oras;
    Data begin;
    Data end;
    cout << "Dati perioada de inceput a croazierei aici:" << endl;
    begin.is_ui = true;
    cin >> begin;
    begin.is_ui = false;
    cout << "Dati finalul perioadei de croaziera aici:" << endl;
    end.is_ui = true;
    cin >> end;
    end.is_ui = false;
    vector<Booking> result = this->sv.search_booking_oras_perioada(oras, begin, end);
    if(result.empty())
        cout << "NU AVEM NICI HOTELURI SUGERATE NICI DORITE!" << endl;
    else
    {
        if (!result.empty())///Avem hoteluri
        {
            cout << "Oferte:" << endl;
            for (int i = 0; i < result.size(); i++)
                cout << i + 1 << " " << endl << result.at(i);
        }

        int nr;
        do {
            cout << "Introduceti numarul ofertei:";
            cout.flush();
            cin >> nr;
        }while(nr>result.size() || nr <= 0);
        nr--;
        if(begin == this->sv.get_elems()[nr].get_data_inc() && end == this->sv.get_elems()[nr].get_data_sf())///acopera tot intervalul
            this->sv.modify(result[nr].get_cod(), result[nr].get_nume(),result[nr].get_oras(), result[nr].get_data_sf().bigger_with_3_days(),result[nr].get_data_sf());
        if(end < this->sv.get_elems()[nr].get_data_sf())///nu acopera tot intervalul; intervalul ramas va fi [end, get_data_sd]
        {
            cout << "S-a facut 1" << endl;
            this->sv.modify(result[nr].get_cod(), result[nr].get_nume(), result[nr].get_oras(), end,
                            result[nr].get_data_sf());
        }
        if(begin > this->sv.get_elems()[nr].get_data_inc())///nu acopera tot intervalul; intervalul ramas va fi [begin, get_data_inc]
        {
            cout << "S-a facut 2" << endl;
            this->sv.modify(result[nr].get_cod(), result[nr].get_nume(), result[nr].get_oras(),
                            result[nr].get_data_inc(), begin);
        }
    }
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