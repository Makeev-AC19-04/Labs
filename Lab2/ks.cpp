#include "ks.h"
#include <iostream>
#include <string>
#include <fstream>

ks::ks()
{
}

ks::~ks()
{
}

int ks::GetId() const
{
    return id;
}

void ks::SetId(int NewId)
{
    id = NewId;
}

string ks::GetName() const
{
    return name;
}

void ks::SetName(string NewName)
{
    name = NewName;
}

int ks::GetNumc() const
{
    return numc;
}

void ks::SetNumc(int NewNumc)
{
    numc = NewNumc;
}

int ks::GetNumcw() const
{
    return numcw;
}

void ks::SetNumcw(int NewNumcw)
{
    numcw = NewNumcw;
}

float ks::GetEffective() const
{
    return effective;
}

void ks::SetEffective(float NewEffective)
{
    effective = NewEffective;
}

using namespace std;

void ks::ReadKs(string file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if (fin.is_open()) {
        fin >> name >> numc >> numcw >> effective;
        fin.close();
    }
    else {
        cout << "Ошибка открытия файла";
    }
}

void ks::WriteName()
{
    cout << "\nВведите название КС\n";
    cin.ignore(32767, '\n');
    getline(cin, name);
}
