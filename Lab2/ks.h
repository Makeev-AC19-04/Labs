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
    vector <int> in = { 0 };
    vector <int> out = { 0 };
    bool done = 0;

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
    void SetIn(int);
    vector <int> GetIn() const;
    void SetOut(int);
    vector <int> GetOut() const;
    string AllIns();
    string AllOuts();
    void ReadIns(string);
    void ReadOuts(string);
    void TryDelIn(int);
    void TruDelOut(int);
    void ClearPipes();
    void SetDone(bool);
    bool GetDone();
};