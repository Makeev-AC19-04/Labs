#include "pipe.h"
#include "ks.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


pipe::pipe()
{
}

pipe::~pipe()
{
}

int pipe::GetId() const
{
    return id;
}

void pipe::SetId(int NewId)
{
    id = NewId;
}

float pipe::GetLength() const
{
    return length;
}

void pipe::SetLength(float NewLength)
{
    length = NewLength;
}

int pipe::GetDiameter() const
{
    return diameter;
}

void pipe::SetDiameter(int NewDiameter)
{
    diameter = NewDiameter;
}

bool pipe::GetFix() const
{
    return fix;
}

void pipe::SetFix(bool NewFix)
{
    fix = NewFix;
}


using namespace std;

void pipe::ReadPipe(string file)
{
    ifstream fin;
    fin.open(file, ios::in);
    if (fin.is_open()) {
        fin >> length >> diameter >> fix;
        fin.close();
    }
    else {
        cout << "Ошибка открытия файла";
    }
}

float pipe::SetPerf()
{
    if (fix != 1) {
        return sqrt(pow(diameter, 5) / length);
    }
    else {
        return 0;
    }
}

int pipe::SetWeight()
{
    int weight;
    if (fix != 1) {
        weight = length;
    }
    else {
        weight = 99999999999999999;
    }
    return weight;
}

float pipe::GetPerf()
{
    return performance;
}

