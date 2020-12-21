#pragma once
#include <vector>
#include "ks.h"
#include "pipe.h"
#include <map>
using namespace std;

class network
{
	map <int, map<int, bool>> MatrSmej;
	vector <vector<pipe>> net;
	map <int, ks> netstations;
	map <int, pipe> netpipes;

public:
	network();
	~network();
	void SetMatr();
	void PrintMatr();
	void SetStations(ks);
	bool CheckKs(int);
	void SetPipes(pipe);
	bool CheckPipe(int);
	bool AreConnected(int, int);
	int FindKs(int);
	void SortNet();
	bool IsTree();
	void change(vector <pipe>, vector <ks>);
};