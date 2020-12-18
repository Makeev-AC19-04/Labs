#include "network.h"
#include <vector>


network::network()
{
}

void network::SetMatr(vector<vector<bool>>)
{
}

void network::SetStations(ks k)
{
	netstations.push_back(k);
}

vector<ks> network::GetStations() const
{
	return netstations;
}

bool network::CheckKs(ks k)
{
	int i;
	for (i = 0; i <= netstations.size(); i++) {
		if (netstations[i].GetId() == k.GetId()) {
			return true;
		}
	}
	return false;
}

void network::DelKs(ks k)
{
	int i;
	for (i = 0; i <= netstations.size(); i++) {
		if (netstations[i].GetId() == k.GetId()) {
			netstations.erase(netstations.begin() + i - 1);
		}
	}
}

void network::SetPipes(pipe p)
{
	netpipes.push_back(p);
}

bool network::CheckPipe(pipe p)
{
	int i;
	for (i = 0; i <= netpipes.size(); i++) {
		if (netpipes[i].GetId() == p.GetId()) {
			return true;
		}
	}
	return false;
}


