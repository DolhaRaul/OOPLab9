//
// Created by rauld on 05.05.2022.
//

#ifndef LAB9_LIVE_REPOSITORY_H
#define LAB9_LIVE_REPOSITORY_H
#include "Booking.h"
#include <vector>
#include <algorithm>
using namespace std;
class Repository{
protected:
    vector<Booking> elems;
public:
    Repository();
    ///param:Un booking transmis prin referinta
    ///return:1 daca bokking ul a fost adaugat sau 0 in caz contrar(Exista deja un booking cu COD unic == b.cod)
    virtual int adaugare(Booking &);
    ///Avem nevoie doar de un cod Pentru a sterge un Booking
    virtual int stergere(int);
    ///Avem nevoie doar de un cod Pentru a sterge un Booking
    virtual int modificare(Booking &);
    virtual int get_size();
    virtual vector<Booking> get_All();
    Repository& operator=(Repository &r);
    virtual ~Repository();
};
#endif //LAB9_LIVE_REPOSITORY_H
