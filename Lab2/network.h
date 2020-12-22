#pragma once
#include <map>
#include "ks.h"
#include "pipe.h"


class network
{
	map <int, ks> stations;
	map <int, pipe> pipes;

public:
	void SetStations(ks);
	bool CheckStations(ks); //проверка на наличие КС в сети
	bool CheckPipes(pipe); //проверка трубы соответственно
	void PrintWebKses();
	void SetPipes(pipe);
	void SetKsIn(int, pipe);
	void SetKsOut(int, pipe);
	void DelKs(int);
	void DelPipe(int);
	void LoadNet();
	void SaveNet();
};

