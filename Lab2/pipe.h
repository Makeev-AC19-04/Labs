#pragma once
#include <string>
#include "ks.h"
using namespace std;

class pipe
{
    int id;
    float length;
    int diameter;
    bool fix;
    float performance = SetPerf();
    int weight = SetWeight();

public:
    pipe();
    ~pipe();
    int GetId() const;
    void SetId(int);
    float GetLength() const;
    void SetLength(float);
    int GetDiameter() const;
    void SetDiameter(int);
    bool GetFix() const;
    void SetFix(bool);
    void ReadPipe(string);
    float SetPerf();
    int SetWeight();
    float GetPerf();
};

