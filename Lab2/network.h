#pragma once
#include <vector>
#include "ks.h"
#include "pipe.h"
using namespace std;

class network
{
	vector <vector<bool>> MatrSmej;
	vector <vector<pipe>> net;
	vector <ks> netstations;
	vector <pipe> netpipes;

public:
	void SetMatr(vector<vector<bool>>);
	void SetStations(ks);
	vector<ks> GetStations() const;
	bool CheckKs(ks);
	void DelKs(ks);
	void SetPipes(pipe);
	bool CheckPipe(pipe);
};

