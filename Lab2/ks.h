#pragma once
#include <string>
#include <vector>
#include "pipe.h"
using namespace std;

class ks
{
    int id;
    string name;
    int numc;
    int numcw;
    float effective;
    vector <int> in;
    vector <int> out;

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
    void SetIn(pipe);
    vector <int> GetIn() const;
    void SetOut(pipe);
    vector <int> GetOut() const;
    string AllIns();
    string AllOuts();
    void ReadIns(string);
    void ReadOuts(string);
    void TryDelIn(int);
    void TruDelOut(int);
};