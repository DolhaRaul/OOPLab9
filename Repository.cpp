//
// Created by rauld on 05.05.2022.
//

#include "Repository.h"
Repository::Repository()
{
}
int Repository::adaugare(Booking &b)
{
    vector<Booking>::iterator it = find(this->elems.begin(), this->elems.end(), b);
    if(it == this->elems.end())///NU MAI EXISTA un asemena booking
    {
        Booking copy(b);
        this->elems.push_back(copy);
        return 1;
    }
    return 0;
}
int Repository::stergere(int cod)
{
    for(int i = 0; i < this->get_size(); i++)
        if(this->elems[i].get_cod() == cod)///Am gasit elementul
        {
            for(int j = i; j < this->get_size() - 1; j++)
                this->elems[j] = this->elems[j + 1];
            elems.pop_back();///Avem cu un element mai putin, TREBUIE sa modificam dimensiunea!
            return 1;
        }
    return 0;
}
int Repository::modificare(Booking &b)
{
    vector<Booking>::iterator it = find(this->elems.begin(), this->elems.end(), b);
    if(it != this->elems.end())///Exista deja un booking ce are acelasi cod cu b.cod
    {
        *it = b;
        return 1;///am modificat
    }
    return 0;
}
vector<Booking> Repository::get_All() {
    return this->elems;
}
int Repository::get_size() {
    return this->elems.size();
}
Repository& Repository::operator=(Repository &r)
{
    if(this != &r)
    {
        this->elems.resize(r.get_size());
        for(int i = 0; i < this->get_size(); i++)
            this->elems[i] = r.elems[i];
    }
    return *this;
}
Repository::~Repository() {}