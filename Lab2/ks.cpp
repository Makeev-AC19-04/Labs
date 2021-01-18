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

void ks::SetIn(int p)
{
    in.push_back(p);
}

vector <int> ks::GetIn() const
{
    return in;
}

void ks::SetOut(int p)
{
    out.push_back(p);
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
        str.append(",");
    }
    str.append(";");
    return str;
}

void ks::ReadIns(string s)
{
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ',' && s[i] != ' ' && s[i] != '0' && s[i] != ';') {
            in.push_back(s[i] - '0');
        }
        else if (s[i] == ';') {
            break;
        }
    }
}

string ks::AllOuts()
{
    string str;
    for (auto& i : out) {
        str.append(to_string(i));
        str.append(",");
    }
    str.append(";");
    return str;
}

void ks::ReadOuts(string s)
{
    for (int i = 0; i < s.length(); ++i) {
        if (s[i] != ',' && s[i] != ' ' && s[i] != '0' && s[i] != ';') {
            out.push_back(s[i] - '0');
        }
        else if (s[i] == ';') {
            break;
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

void ks::ClearPipes()
{
    in = { 0 };
    out = { 0 };
}

void ks::SetDone(bool b)
{
    done = b;
}

bool ks::GetDone()
{
    return done;
}


