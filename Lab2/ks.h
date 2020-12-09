#pragma once
#include <string>
using namespace std;

class ks
{
    int id;
    string name;
    int numc;
    int numcw;
    float effective;

public:
    ks();
    ~ks();
    int GetId() const;
    void SetId(int);
    string GetName() const;
    void SetName(string);
    int GetNumc() const;
    void SetNumc(int);
    int GetNumcw() const;
    void SetNumcw(int);
    float GetEffective() const;
    void SetEffective(float);
    void ReadKs(string);
    void WriteName();
};

