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

};

