//
// Created by rauld on 05.05.2022.
//

#ifndef LAB9_LIVE_BOOKING_H
#define LAB9_LIVE_BOOKING_H
#include <cstring>
#include <iostream>
#include <sstream>
#include "Data.h"
using namespace std;

class Booking{
private:
    int cod;
    string nume;
    string oras;
    Data data_inc;
    Data data_sf;
public:
    Booking();
    Booking(int, string, string, Data, Data);
    Booking(const Booking &b);
    int get_cod();
    string get_nume();
    string get_oras();
    Data get_data_inc();
    Data get_data_sf();
    void set_cod(int);
    void set_nume(string);
    void set_oras(string);
    void set_data_inc(Data&);
    void set_data_sf(Data&);
    Booking& operator=(Booking &);
    ///param:Un booking trimis prin referinta
    ///return:1 daca booking urile au acelasi cod(Acestea sunt unic identificate prin cod) sau 0 in caz contrar
    bool operator==(const Booking &);
    bool operator!=(const Booking&);
    friend ostream& operator<<(ostream& os, Booking&);
    friend istream& operator>>(istream& is, Booking&);
    string to_string();
    static Booking from_string(string);
};
#endif //LAB9_LIVE_BOOKING_H
