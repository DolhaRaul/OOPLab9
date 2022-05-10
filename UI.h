//
// Created by rauld on 09.05.2022.
//

#ifndef MAIN_CPP_UI_H
#define MAIN_CPP_UI_H
#include "Service.h"
#include "Repository.h"
#include "Booking.h"
#include <iostream>
#include <string>
using namespace std;
class UI{
private:
    Service sv;
    void adaugare();
    void stergere();
    void modificare();
    void numar_entitati();
    void cautare_hotele();
    void cautare_hotele_oras_perioada();
    void show_all();
public:
    UI();
    UI(Service &);
    void show_menu();
    void run_menu();
    ~UI();
};
#endif //MAIN_CPP_UI_H
