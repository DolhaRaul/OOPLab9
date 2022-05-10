//
// Created by rauld on 05.05.2022.
//

#include "Booking.h"
Booking::Booking() {
    this->cod = 0;
    this->nume = new char[20];
    strcpy_s(this->nume, 10, "nimic");
    this->oras = new char[20];
    strcpy_s(this->oras, 10, "nimic");
    this->data_inc.zi = 1;
    this->data_inc.luna = 1;
    this->data_inc.an = 1;
    this->data_sf.zi = 1;
    this->data_sf.luna = 1;
    this->data_sf.an = 1;
}
Booking::Booking(int cod, char*nume, char* oras, Data data_inc, Data data_sf) {
    this->cod = cod;
    this->nume = new char[strlen(nume) + 1];
    strcpy_s(this->nume, strlen(nume) + 1, nume);
    this->oras = new char[strlen(oras) + 1];
    strcpy_s(this->oras, strlen(oras) + 1, oras);
    this->data_inc = data_inc;
    this->data_sf = data_sf;
}
Booking::Booking(const Booking &b) {
    this->cod = b.cod;
    this->nume = new char[strlen(b.nume) + 1];
    strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);
    this->oras = new char[strlen(b.oras) + 1];
    strcpy_s(this->oras, strlen(b.oras) + 1, b.oras);
    this->data_inc = b.data_inc;
    this->data_sf = b.data_sf;
}
int Booking::get_cod() {
    return this->cod;
}
char* Booking::get_nume() {
    return this->nume;
}
char* Booking::get_oras() {
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
void Booking::set_nume(char *nume) {
    if(this->nume)
        delete[] this->nume;
    this->nume = new char[strlen(nume) + 1];
    strcpy_s(this->nume, strlen(nume) + 1, nume);
}
void Booking::set_oras(char* oras) {
    if(this->oras)
        delete[] this->oras;
    this->oras = new char[strlen(oras) + 1];
    strcpy_s(this->oras, strlen(oras) + 1, oras);
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
        if(this->nume)
            delete[] this->nume;
        this->nume = new char[strlen(b.nume) + 1];
        strcpy_s(this->nume, strlen(b.nume) + 1, b.nume);
        if(this->oras)
            delete[] this->oras;
        this->oras = new char[strlen(b.oras) + 1];
        strcpy_s(this->oras, strlen(b.oras) + 1, b.oras);
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
    os << "Pentru data_Inceput_Disponibilitate: " << endl << b.data_inc;
    os << "Pentru data_Sfarsit_Disponibilitate: " << endl << b.data_sf << endl;
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
    is >> b.data_inc;
    cout << "Pentru data_Sfarsit_Disponibilitate, avem:" << endl;
    is >> b.data_sf;
    return is;
}
char* Booking::to_string()
{
    char* sir= new char[50];///sirul returnat
    char* aux_cod = new char[5];
    strcpy(sir, "");
    itoa(this->cod, aux_cod, 10);
    strcat(sir, aux_cod);strcat(sir, " ");
    strcat(sir, this->nume);strcat(sir, " ");
    strcat(sir, this->oras);strcat(sir, " ");
    strcat(sir, this->data_inc.to_string());strcat(sir, " ");
    strcat(sir, this->data_sf.to_string());strcat(sir, " ");
    return sir;
}
Booking Booking::from_string(char * s) {
    Booking b;
    char* p =strtok(s, " ");
    b.cod = atoi(p);
    p= strtok(NULL, " ");
    strcpy(b.nume, p);
    p= strtok(NULL, " ");
    strcpy(b.oras, p);
    char ds[20]={0};
    for(int i=0;i<3;++i) {
        p = strtok(NULL, " ");
        if(p==NULL) break;
        strcat(ds, p);
        strcat(ds, " ");
    }
    b.data_inc = Data::from_string(ds);
    strcpy(ds, "");
    for(int i=0;i<3;++i) {
        p = strtok(NULL, " ");
        if(p==NULL) break;
        strcat(ds, p);
        strcat(ds, " ");
    }
    b.data_sf = Data::from_string(ds);
    return b;
}
Booking::~Booking() {
    if(this->nume)
        delete[] this->nume;
    if(this->oras)
        delete[] this->oras;
}

