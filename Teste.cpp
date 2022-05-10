//
// Created by rauld on 05.05.2022.
//

#include "Teste.h"
#include <iostream>
#include <cassert>
using namespace std;
void Teste::teste_entitate()
{
    cout << "Teste pentru entitate:" << endl;
    Booking b;
    assert(b.get_cod() == 0);
    assert(b.get_nume()=="nimic");///datele initiale sunt bune

    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    assert(Data::from_string(s1.to_string()).luna == s1.luna);
    Booking b1(1, "Ozana", "Bistrita", s1, s2);
    assert(b1.get_data_inc().zi == 1);
    assert(b1.get_data_inc().luna == 1);
    assert(b1.get_data_inc().an == 1);
    assert(b1.get_data_sf().zi == 2);
    assert(b1.get_oras()== "Bistrita");
    Data s1_nume = {3, 3, 3};
    b1.set_data_inc(s1_nume);///Schimbam nuumele
    assert(b1.get_data_inc().zi == 3);
    assert(b1.get_data_inc().luna == 3);
    assert(b1.get_data_inc().an == 3);///Numele s a setat cu succes!

    Booking b2 = b1;
    assert(b2.get_data_sf().zi == b1.get_data_sf().zi);
    assert(b2.get_cod() == b1.get_cod());///se copiaza bine parametrii
    assert(b2 == b1);
    assert(b2 != b);///Operatii == si != merg su cucces

    b2.set_cod(3);
    assert(b2.get_cod() == 3);
    b2.set_oras("Vaslui");
    assert(b2.get_oras()== "Vaslui");
    b2.set_nume("monopoly");
    assert(b2.get_nume()== "monopoly");

    assert(Booking::from_string(b2.to_string()) == b2);
    assert(Booking::from_string(b1.to_string()) == b1);
    assert(Booking::from_string(b.to_string()) == b);
    cout << "Testele pentru entitate sunt ok!" << endl;
}
void Teste::teste_repository_live()
{
    cout << "Teste repository live:" << endl;
    Repository r;
    assert(r.get_size() == 0);///Nu avem elemente initial
    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    Booking b1(1, "Ozana", "Bistrita", s1, s2);
    r.adaugare(b1);
    assert(r.get_size() == 1);
    assert(r.get_All()[0] == b1);///Entitatea s a adaugat succes
    r.adaugare(b1);
    assert(r.get_size() == 1);///Nu se poate adauga iar b1, FIINDCA SE REPETA CODUL UNIC
    cout << "Testele pentru repository live sunt ok!" << endl;
}
void Teste::teste_repository_tema()
{
    cout << "Teste repository tema:" << endl;
    Repository r;
    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    Data s3 = {11, 1, 2012};
    Data s4 = {11, 11, 2020};
    Booking b1(1, "Ozana", "Bistrita", s1, s2);
    r.adaugare(b1);
    assert(r.get_size() == 1);
    Booking b2(2, "metropolis", "Bistrita", s1, s2);
    Booking b3(5, "Fagaras", "Monor", s3, s4);
    Booking b4(6, "metropolis", "Bistrita", s1, s2);
    r.adaugare(b2);
    r.adaugare(b3);
    r.adaugare(b4);
    assert(r.get_size() == 4);
    assert(r.stergere(1) == 1);///S a sters cu succes primul Booking!
    assert(r.get_size() == 3);
    assert(r.stergere(b1.get_cod()) == 0);///B1 nu mai exista!
    Booking b1_new(1, "LaMinuta", "Bistrita", s1, s2);
    assert(r.modificare(b1_new) == 0);///Nu avem cum sa modificam FIINDCA AM STERS PE b1
    assert(r.adaugare(b1) == 1);///Nu mai exista alt booking cu acest id
    assert(r.modificare(b1_new) == 1);///Acum putem modifica!
    cout << "Testele pentru repository tema sunt ok!" << endl;
}
void Teste::teste_service_tema()
{
    cout << "Metodele tema si una live pentru service:" << endl;
    Repository r;
    Service sv(r);
    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    Data s3 = {11, 1, 2012};
    Data s4 = {11, 11, 2020};
    Booking b1_new(1, "LaMinuta", "Bistrita", s1, s2);
    Booking b2(2, "metropolis", "Bistrita", s1, s2);
    Booking b3(5, "Fagaras", "Monor", s3, s4);
    Booking b4(6, "metropolis", "Bistrita", s1, s2);
    sv.add(1, "LaMinuta", "Bistrita", s1, s2);
    assert(sv.get_nr_elem() == 1);///S a adaugat cu succes elementul!
    assert(sv.get_elems()[0] == b1_new);
    assert(sv.add(1, "LaMinuta", "Bistrita", s1, s2) == 0);///Elementul a fost deja adaugat!
    assert(sv.add(2, "metropolis", "Bistrita", s1, s2) == 1);
    sv.add(5, "Fagaras", "Monor", s3, s4);
    sv.add(6, "metropolis", "Bistrita", s1, s2);

    assert(sv.get_nr_elem() == 4);
    assert(sv.del(1) == 1);///S a sters cu succes elementul!
    assert(sv.del(1) == 0);///Acum nu il mai putem sterge!
    assert(sv.get_nr_elem() == 3);
    assert(sv.get_elems()[0] == b2);///b2 e acum primul booking

    assert(sv.modify(1, "LaMinuta", "Bistrita", s1, s2) == 0);///NU il putem Modifica; Acest booking fu STERS!
    assert(sv.add(1, "LaMinuta", "Bistrita", s1, s2) == 1);
    assert(sv.modify(1, "LaRaul", "Bistrita", s3, s3) == 1);///ACUM PUTEM!

    Service sv_nou;
    sv_nou = sv;
    assert(sv_nou.get_nr_elem() == sv.get_nr_elem());///MERGE ATRIBUIREA!
    vector<Booking> hotele = sv.search_after_oras("Bistrita");
    assert(hotele.size() == 3);///Avem 3 hoteluri Bistrita
    assert(hotele[0] == Booking(2, "metropolis", "Bistrita", s1, s2));///Primul hotel!
    sv.add(33, "LaRaul", "Magulesti", s3, s3);
    hotele = sv.search_after_oras("LaRaul");
    assert(hotele.capacity() == 0);///Nu avem hoteluri cu acest nume!
    cout << "Metodele tema si una live pentru service sunt bune!" << endl;
}

void Teste::teste_repository_file(){
    ofstream fout("file.txt"); fout.close(); // creez
    RepositoryInFile r("file.txt");
    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    Data s3 = {11, 1, 2012};
    Data s4 = {11, 11, 2020};
    Booking b1_new(1, "LaMinuta", "Bistrita", s1, s2);
    Booking b2(2, "metropolis", "Bistrita", s1, s2);
    Booking b3(5, "Fagaras", "Monor", s3, s4);
    Booking b4(6, "metropolis", "Bistrita", s1, s2);
    r.adaugare(b1_new);
    r.adaugare(b2);
    r.adaugare(b3);
    r.adaugare(b4);
    assert(r.get_size()==4);
//    r.stergere(b2.get_cod());
//    assert(r.get_size()==3);
    ::remove("file.txt");
}
void Teste::teste_operatori_data()
{
    ///Teste pentru operatori
    Data s1 = {1, 1, 1};
    Data s2 = {2, 2, 2};
    Data s3 = {11, 1, 2012};
    Data s4 = {11, 11, 2020};
    assert(s1 < s2);
    assert(s1 <= s2);
    assert(s1 == s1);
    assert(s3 < s4);
    assert(s4 > s3);
    assert(s4 >= s3);
    ///SUNT OK!
    ///Teste pentru bigger_with_3_days;
    Data result = s1.bigger_with_3_days();
    assert(result.zi == 4 && result.luna == 1 && result.an == 1);
    s1 = {28, 3, 2022};
    result = s1.bigger_with_3_days();
    assert(result.zi == 31 && result.luna == 3 && result.an == 2022);
    s1 = {23, 4, 1111};
    result = s1.bigger_with_3_days();
    assert(result.zi == 26 && result.luna == 4 && result.an == 1111);
    s1 = {30, 9, 2011};
    result = s1.bigger_with_3_days();
    assert(result.zi == 3 && result.luna == 10 && result.an == 2011);
    s1 = {30, 12, 2000};
    result = s1.bigger_with_3_days();
    assert(result.zi == 2 && result.luna == 1 && result.an == 2001);
    s1 = {10, 12, 2000};
    result = s1.bigger_with_3_days();
    assert(result.zi == 13 && result.luna == 12 && result.an == 2000);
    s1 = {27, 2, 1999};;
    result = s1.bigger_with_3_days();
    assert(result.zi == 2 && result.luna == 3 && result.an == 1999);
    s1 = {20, 2, 1999};;
    result = s1.bigger_with_3_days();
    assert(result.zi == 23 && result.luna == 2 && result.an == 1999);
    ///SUNT OK!
    ///Teste pentru lower_with_3_keys
    s2 = {28, 2, 2022};
    result = s2.lower_with_3_days();
    assert(result.zi == 25 && result.luna == 2 && result.an == 2022);
    s2 = {4, 8, 2022};
    result = s2.lower_with_3_days();
    assert(result.zi == 1 && result.luna == 8 && result.an == 2022);
    s2 = {9, 5, 2000};;
    result = s2.lower_with_3_days();
    assert(result.zi == 6 && result.luna == 5 && result.an == 2000);
    s2 = {2, 12, 1};
    result = s2.lower_with_3_days();
    assert(result.zi == 29 && result.luna == 11 && result.an == 1);
    s2 = {1, 5, 2000};
    result = s2.lower_with_3_days();
    assert(result.zi == 28 && result.luna == 4 && result.an == 2000);
    s2 = {15, 1, 2000};
    result = s2.lower_with_3_days();
    assert(result.zi == 12 && result.luna == 1 && result.an == 2000);
    s2 = {2, 1, 2001};
    result = s2.lower_with_3_days();
    assert(result.zi == 30 && result.luna == 12 && result.an == 2000);
    s2 = {1, 3, 2000};
    result = s2.lower_with_3_days();
    assert(result.zi == 26 && result.luna == 2 && result.an == 2000);
    s2 = {12, 3, 1000};
    result = s2.lower_with_3_days();
    assert(result.zi == 9 && result.luna == 3 && result.an == 1000);
}