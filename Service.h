//
// Created by rauld on 09.05.2022.
//

#ifndef MAIN_CPP_SERVICE_H
#define MAIN_CPP_SERVICE_H
#include "Repository.h"
#include "RepositoryInFile.h"
#include "Booking.h"
class Service{
private:
    Repository& repo;
    ///RepositoryInFile repo;
    ///param:4 date, care formeaza 2 intervale [inceput1, sfarsit1] = perioada1, [inceput2, sfarsit2] = perioada2
    ///return1:true daca perioada1 e inclusa in perioada 2 sau false in caz contrar
    ///OBS:Datele trebuie sa formeze corect intervalul!
    bool verify_period(Data inceput1, Data sfarsit1, Data inceput2, Data sfarsit2);
public:
    Service(Repository & r):repo(r){}
    ///ultimele 6 int uri ne dau cele 2 dati
    int add(int, string , string , Data, Data);
    ///Avem nevoie doar de un cod pentru a sterge un Booking
    int del(int);
    int modify(int, string , string , Data, Data);
    int get_nr_elem();
    vector<Booking> get_elems();
    ///param:Un nume de hotel dat ca parametru
    ///return:Toate booking urile ce au numele hotelului cel dat ca parametru
    vector<Booking> search_after_oras(string );
    vector<Booking> search_booking_oras_perioada(string , Data&, Data&);
    Service& operator=(Service &);
    ~Service();
};
#endif //MAIN_CPP_SERVICE_H
