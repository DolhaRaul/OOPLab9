//
// Created by rauld on 10.05.2022.
//

#ifndef MAIN_CPP_REPOSITORYINFILE_H
#define MAIN_CPP_REPOSITORYINFILE_H
#include "Repository.h"
#include <fstream>
using namespace std;
class RepositoryInFile:public Repository{
private:
    char* fisier;
    void loadFromFile();
    void storeToFile();
public:
    RepositoryInFile();
    RepositoryInFile(char*);
    int adaugare(Booking &) override;
    ///Avem nevoie doar de un cod Pentru a sterge un Booking
    int stergere(int) override;
    ///Avem nevoie doar de un cod Pentru a sterge un Booking
    int modificare(Booking &) override;
    int get_size() override;
    vector<Booking> get_All() override;
    RepositoryInFile& operator=(RepositoryInFile &);
};

#endif //MAIN_CPP_REPOSITORYINFILE_H
