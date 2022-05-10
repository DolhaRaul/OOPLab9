//
// Created by rauld on 05.05.2022.
//

#ifndef LAB9_LIVE_BOOKING_H
#define LAB9_LIVE_BOOKING_H
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;
struct Data{
    int zi;
    int luna;
    int an;
    friend ostream& operator<<(ostream& os, Data& data)
    {
        os << "Ziua datei este: " << data.zi << endl;
        os << "Luna datei este: " << data.luna << endl;
        os << "Anul datei este: " << data.an << endl;
        return os;
    }
    friend istream& operator>>(istream &is, Data& data)
    {
        cout << "Dati ziua datei: ";
        is >> data.zi;
        cout << endl;
        cout << "Dati luna datei: ";
        is >> data.luna;
        cout << endl;
        cout << "Dati anul datei: ";
        is >> data.an;
        cout << endl;
        return is;
    }
    char* to_string(){
        stringstream ss;
        ss<<zi<<' '<<luna<<' '<<an;
        const char* buf = ss.str().c_str();
        char* rez = new char[15];
        strcpy(rez, buf);
        return rez;
    }
    static Data from_string(char* sir)
    {
        Data rez;
        istringstream ss(sir);
        ss>>rez.zi>>rez.luna>>rez.an;
        return rez;
    }
    bool operator==(Data &data)
    {
        return this->zi == data.zi &&
        this->luna == data.luna &&
        this->an == data.an;
    }
    bool operator<(Data& data)
    {
        if(this->an < data.an)
            return true;
        if(this->an == data.an)
        {
            if (this->luna < data.luna)
                return true;
            if (this->luna == data.luna)
                if (this->zi < data.zi)
                    return true;
        }
        return false;
    }
    bool operator<=(Data &data)
    {
        if(*this < data)
            return true;///Avem relatie stricta
        if(*this == data)
            return true;
        return false;
    }
    bool operator>(Data &data)
    {
        return !(*this <= data);
    }
    bool operator>=(Data &data)
    {
        return !(*this < data);
    }
    Data bigger_with_3_days()
    {
        ///luna 12 == decemebrie o tratam separat, fiindca se poate sa trecem la urmatorul an
        ///la fel luna 2 == februarie
        Data result = *this;
        if(this->luna == 1 || this->luna == 3 || this->luna == 5 || this->luna == 7 || this->luna == 8 || this->luna == 10)
        {
            if(this->zi + 3 <= 31)///nu schimbam
            {
                result.zi = this->zi + 3;
                return result;
            }
            if(this->zi + 3 > 31)
            {
                result.zi = this->zi + 3 - 31;
                result.luna++;
                return result;
            }
        }
        if(this->luna == 4 || this->luna == 6 || this->luna == 9 || this->luna == 11)
        {
            if(this->zi + 3 <= 30)///nu schimbam
            {
                result.zi = this->zi + 3;
                return result;
            }
            if(this->zi + 3 > 30)
            {
                result.zi = this->zi + 3 - 30;
                result.luna++;
                return result;
            }
        }
        if(this->luna == 2)
        {
            if(this->zi + 3 <= 28)///nu schimbam
            {
                result.zi += 3;
                return result;
            }
            if(this->zi + 3 > 28)
            {
                result.zi = this->zi + 3 - 28;
                result.luna++;
                return result;
            }
        }
        if(this->luna == 12)
        {
            if(this->zi + 3 <= 31)///nu schimbam
            {
                result.zi += 3;
                return result;
            }
            if(this->zi + 3 > 31)
            {
                result.zi = this->zi + 3 - 31;
                result.luna = 1;///Incepem un nou an
                result.an++;
                return result;
            }
        }
    }
    Data lower_with_3_days()
    {
        Data result = *this;
        ///lunile care au 30(sau 28, februarie sau 30, august) de zile si sunt precedate de o luna cu 31 de zile
        if(this->luna == 2 || this->luna == 4 || this->luna == 6 || this->luna == 8 || this->luna == 9 || this->luna == 11)
        {
            if(this->zi >= 4)
            {
                result.zi -= 3;
                return result;
            }
            if(this->zi <= 3)
            {
                result.zi -= 3;
                result.zi += 31;
                result.luna--;///revenim in luna precedenta
                return result;
            }
        }
        ///lunile care au 31 de zile si sunt precedate de o luna care au 30 de zile
        if(this->luna == 5 || this->luna == 7 || this->luna == 10 || this->luna == 12)
        {
            if(this->zi >= 4)
            {
                result.zi -= 3;
                return result;
            }
            if(this->zi <= 3)
            {
                result.zi -= 3;
                result.zi += 30;
                result.luna--;///revenim in luna precedenta
                return result;
            }
        }
        ///e prima luna
        if(this->luna == 1) {
            if (this->zi >= 4)
            {
                result.zi -= 3;
                return result;
            }
            if (this->zi <= 3)
            {
                result.zi -= 3;
                result.zi += 31;
                result.luna = 12;///revenim in luna precedenta, luna decmbrie si incepem anul anterior
                result.an--;
                return result;
            }
        }
        ///luna martie, precedata de februarie cu 28 de zile
        if(this->luna == 3)
        {
            if(this->zi >= 4)
            {
                result.zi -= 3;
                return result;
            }
            if(this->zi <= 3)
            {
                result.zi -= 3;
                result.zi += 28;
                result.luna--;///revenim in luna precedenta
                return result;
            }
        }
    }
};
class Booking{
private:
    int cod;
    char* nume;
    char* oras;
    Data data_inc;
    Data data_sf;
public:
    Booking();
    Booking(int, char*, char*, Data, Data);
    Booking(const Booking &b);
    int get_cod();
    char* get_nume();
    char* get_oras();
    Data get_data_inc();
    Data get_data_sf();
    void set_cod(int);
    void set_nume(char*);
    void set_oras(char*);
    void set_data_inc(Data&);
    void set_data_sf(Data&);
    Booking& operator=(Booking &);
    ///param:Un booking trimis prin referinta
    ///return:1 daca booking urile au acelasi cod(Acestea sunt unic identificate prin cod) sau 0 in caz contrar
    bool operator==(const Booking &);
    bool operator!=(const Booking&);
    friend ostream& operator<<(ostream& os, Booking&);
    friend istream& operator>>(istream& is, Booking&);
    char* to_string();
    static Booking from_string(char*);
    ~Booking();
};
#endif //LAB9_LIVE_BOOKING_H
