#include "ks.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>


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
    string ins, outs;
    fin.open(file, ios::in);
    if (fin.is_open()) {
        fin >> name >> numc >> numcw >> effective >> ins >> outs;
        ReadIns(ins);
        ReadOuts(outs);
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

void ks::SetIn(pipe p)
{
    in.push_back(p.GetId());
}

vector <int> ks::GetIn() const
{
    return in;
}

void ks::SetOut(pipe p)
{
    out.push_back(p.GetId());
}

vector <int> ks::GetOut() const
{
    return out;
}

string ks::AllIns()
{
    string str;
    for (auto& i : in) {
        str.append(to_string(i));
        str.append(", ");
    }
    return str;
}

void ks::ReadIns(string s)
{
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ',' && s[i] != ' ') {
            in.push_back(s[i]);
        }
    }
}

string ks::AllOuts()
{
    string str;
    for (auto& i : out) {
        str.append(to_string(i));
        str.append(", ");
    }
    return str;
}

void ks::ReadOuts(string s)
{
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ',' && s[i] != ' ') {
            out.push_back(s[i]);
        }
    }
}

void ks::TryDelIn(int d)
{
    in.erase(std::remove(in.begin(), in.end(), d), in.end());
}

void ks::TruDelOut(int d)
{
    out.erase(std::remove(out.begin(), out.end(), d), out.end());
}


