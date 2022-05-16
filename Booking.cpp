//
// Created by rauld on 05.05.2022.
//

#include "Booking.h"
Booking::Booking() {
    this->cod = 0;
    this->nume="nimic";
    this->oras= "nimic";
    this->data_inc.zi = 1;
    this->data_inc.luna = 1;
    this->data_inc.an = 1;
    this->data_sf.zi = 1;
    this->data_sf.luna = 1;
    this->data_sf.an = 1;
}
Booking::Booking(int cod, string nume, string oras, Data data_inc, Data data_sf) {
    this->cod = cod;
    this->nume = nume;
    this->oras = oras;
    this->data_inc = data_inc;
    this->data_sf = data_sf;
}
Booking::Booking(const Booking &b) {
    this->cod = b.cod;
    this->nume = b.nume;
    this->oras = b.oras;
    this->data_inc = b.data_inc;
    this->data_sf = b.data_sf;
}
int Booking::get_cod() {
    return this->cod;
}
string Booking::get_nume() {
    return this->nume;
}
string Booking::get_oras() {
    return this->oras;
}
Data Booking::get_data_inc() {
    return this->data_inc;
}
Data Booking::get_data_sf() {
    return this->data_sf;
}
void Booking::set_cod(int cod) {
    this->cod = cod;
}
void Booking::set_nume(string nume) {
    this->nume = nume;
}
void Booking::set_oras(string oras) {
    this->oras=oras;
}
void Booking::set_data_inc(Data &data_inceput) {
   this->data_inc = data_inceput;
}
void Booking::set_data_sf(Data &data_sfarsit) {
   this->data_sf = data_sfarsit;
}
Booking& Booking::operator=(Booking &b) {
    if(this != &b)///Putem sschimba/atribui un BOOKING doar daca au acelasi cod
    {
        this->cod = b.cod;
        this->nume = b.nume;
        this->oras = b.oras;
        this->data_inc = b.data_inc;
        this->data_sf = b.data_sf;
    }
    return *this;
}
bool Booking::operator==(const Booking &b) {
    return(this->cod == b.cod);///Codul trebuie sa fie unic; U
}
bool Booking::operator!=(const Booking &b) {
    return !(*this == b);
}
ostream& operator<<(ostream& os, Booking &b)
{
    os << "Codul booking ului este: " << b.cod << endl;
    os << "Numele hotelui booking ului este: " << b.nume << endl;
    os << "Orasul hotelului booking ului este: " << b.oras << endl;
    b.data_inc.is_ui = true;
    b.data_sf.is_ui = true;
    os << "Pentru data_Inceput_Disponibilitate: " << endl << b.data_inc << endl;
    os << "Pentru data_Sfarsit_Disponibilitate: " << endl << b.data_sf << endl;
    b.data_inc.is_ui = false;
    b.data_sf.is_ui = false;
    return os;
}
istream& operator>>(istream &is, Booking &b)
{
    cout << "Dati codul booking ului aici: ";
    is >> b.cod;
    cout << endl;
    cout << "Dati numele booking ului aici: ";
    is >> b.nume;
    cout << endl;
    cout << "Dati orasul booking ului aici: ";
    is >> b.oras;
    cout << endl;
    cout << "Pentru data_Inceput_Disponibilitate, avem:" << endl;
    b.data_inc.is_ui = true;
    is >> b.data_inc;
    b.data_inc.is_ui = false;
    cout << "Pentru data_Sfarsit_Disponibilitate, avem:" << endl;
    b.data_sf.is_ui = true;
    is >> b.data_sf;
    b.data_sf.is_ui = true;
    return is;
}
string Booking::to_string()
{
    return std::to_string(cod) + " " + nume + " " + oras + " " + data_inc.to_string() + " " + data_sf.to_string();
}
Booking Booking::from_string(string s) {
    Booking b;
    istringstream is(s);
    is>>b.cod>>b.nume>>b.oras>>b.data_inc>>b.data_sf;
    return b;
}
