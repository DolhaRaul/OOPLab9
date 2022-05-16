//
// Created by rauld on 09.05.2022.
//

#include "Service.h"
bool Service::verify_period(Data inceput1, Data sfarsit1, Data inceput2, Data sfarsit2)
{
    if(inceput1 > sfarsit1)
        return false;///Valorile ce vin ca parametru nu sunt bune
    if(inceput2 > sfarsit2)///Intervalul in care vrem sa cautam INCLUZIUNEA NU E BUN(pentru ca hotelul NU mai e
        return false;   ///disponibil
    if(inceput1 < inceput2)
        return false;
    if(sfarsit1 > sfarsit2)
        return false;
    return true;///inceput2 <= inceput1, sfarsit1 <= sfarsit2
}
int Service::get_nr_elem()
{
    return this->repo.get_size();
}
int Service::add(int cod, string nume, string oras, Data inceput, Data sfarsit)
{
    Booking b(cod, nume, oras, inceput, sfarsit);
    return this->repo.adaugare(b);
}
int Service::del(int cod)
{
    return this->repo.stergere(cod);
}
int Service::modify(int cod_nou, string nume_nou, string oras_nou, Data inc_noua, Data sf_noua)
{
    Booking b_new(cod_nou, nume_nou, oras_nou, inc_noua, sf_noua);
    return this->repo.modificare(b_new);
}
Service& Service::operator=(Service &sv)
{
    if(this != &sv)
        this->repo = sv.repo;///Avem implementat operatorul de atribuire pentru repo!
    return *this;
}
vector<Booking> Service::get_elems()
{
    return this->repo.get_All();
}
vector<Booking> Service::search_after_oras(string oras)
{
    vector<Booking> hotele_dorite;
    for(int i = 0; i < this->get_nr_elem(); i++)
        if(this->get_elems()[i].get_oras()==oras)
            hotele_dorite.push_back(this->get_elems()[i]);
    return hotele_dorite;
}
vector<Booking> Service::search_booking_oras_perioada(string oras, Data &begin, Data &end)
{
    vector<Booking> hoteluri_oras;///cele care au orasul dorit
    for(int i = 0; i < this->get_nr_elem(); i++)
        if(this->get_elems()[i].get_oras()==oras)///au acelasi oras
            hoteluri_oras.push_back(this->get_elems()[i]);
    vector<Booking> hoteluri_dorite;///cele care respecta cerinta
    for(int i = 0; i < hoteluri_oras.size(); i++)
        if(verify_period(begin, end, hoteluri_oras[i].get_data_inc(), hoteluri_oras[i].get_data_sf()))///AM PRINS IN PERIOADA DIPSONIBILA
            hoteluri_dorite.push_back(hoteluri_oras[i]);
    if(!hoteluri_dorite.empty())///avem hoteluri dorite
    {
        return hoteluri_dorite;
    }
    if(hoteluri_dorite.empty())///NU AVEM hoteluri dorite
    {
        vector<Booking> hoteluri_sugerate;
        Data new_begin = begin.bigger_with_3_days();
        Data new_end = end.bigger_with_3_days();///Interval cu 3 zile mai mare
        for(int i = 0; i < hoteluri_oras.size(); i++)
            if(verify_period(new_begin, new_end,hoteluri_oras[i].get_data_inc(), hoteluri_oras[i].get_data_sf()))///Avem un hotel sugerat
                hoteluri_sugerate.push_back(hoteluri_oras[i]);
        new_begin = begin.lower_with_3_days();
        new_end = end.lower_with_3_days();///interval cu 3 zile mai mic
        for(int i = 0; i < hoteluri_oras.size(); i++)
            if(verify_period(new_begin, new_end,hoteluri_oras[i].get_data_inc(), hoteluri_oras[i].get_data_sf()))///Avem un hotel sugerat
                hoteluri_sugerate.push_back(hoteluri_oras[i]);
        return hoteluri_sugerate;///Ca avem elemente, ca nu avem, le returnam
    }
}
Service::~Service() {}