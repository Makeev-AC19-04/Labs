#include "pipe.h"
#include "ks.h"
#include <iostream>
#include <string>
#include <fstream>

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


void pipe::SetIn(ks p)
{
    in = p;
}

ks pipe::GetIn() const
{
    return in;
}

void pipe::SetOut(ks p)
{
    out = p;
}

ks pipe::GetOut() const
{
    return out;
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

