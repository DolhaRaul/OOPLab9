//
// Created by rauld on 10.05.2022.
//

#include "RepositoryInFile.h"
#include "Repository.h"
RepositoryInFile::RepositoryInFile()
{
    this->fisier = new char[10];
    strcpy(this->fisier, "Cazare.txt");
}
RepositoryInFile::RepositoryInFile(char *fisier)
{
    this->fisier = new char[strlen(fisier) + 1];
    strcpy_s(this->fisier, strlen(fisier) + 1, fisier);
}
void RepositoryInFile::loadFromFile()
{
    elems.clear();
    ifstream f(fisier);
    char s[50];
    while(f.getline(s, 50))
    {
        elems.push_back(Booking::from_string(s));
    }
    f.close();
}
void RepositoryInFile::storeToFile() {
    ofstream fout(fisier);
    for(auto& elem : elems)
        fout<<elem.to_string()<<'\n';
    fout.close();
}
int RepositoryInFile::adaugare(Booking &b)
{
    loadFromFile();
    int rez = Repository::adaugare(b);
    storeToFile();
    return rez;
}

int RepositoryInFile::stergere(int elem) {
    loadFromFile();
    int rez = Repository::stergere(elem);
    storeToFile();
    return rez;
}

int RepositoryInFile::modificare(Booking & b) {
    loadFromFile();
    int rez = Repository::modificare(b);
    storeToFile();
    return rez;}

int RepositoryInFile::get_size() {
    loadFromFile();
    return Repository::get_size();
}
RepositoryInFile& RepositoryInFile::operator=(RepositoryInFile &r)
{
    if(this != &r)
    {
        Repository::operator=(r);
        if(this->fisier)
            delete[] this->fisier;
        this->fisier = new char[strlen(r.fisier) + 3];
        strcpy_s(this->fisier, strlen(r.fisier) + 1, r.fisier);
    }
    return *this;
}
vector<Booking> RepositoryInFile::get_All() {
    loadFromFile();
    return Repository::get_All();
}
