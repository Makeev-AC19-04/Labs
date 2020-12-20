#include "network.h"
#include <vector>
#include <iostream>


network::network()
{
}


void network::SetMatr()
{
	vector <vector<bool>> matr(netstations.size(), vector<bool>(netstations.size(), false));
	for (int i = 0; i <= netstations.size(); i++) {
		for (int j = 0; j <= netstations.size(); j++) {
			if (AreConnected(netstations[i].GetId(), netstations[j].GetId())) {
				matr[i][j] = true;
			}
			else
			{
				matr[i][j] = false;
			}
		}
	}
	MatrSmej = matr;
}

void network::PrintMatr()
{
	for (int i = 0; i <= netstations.size(); i++) {
		for (int j = 0; j <= netstations.size(); j++) {
			cout << MatrSmej[i][j] << " ";
		}
		cout << endl;
	}
}

void network::SetStations(ks k)
{
	if (std::find(netstations.begin(), netstations.end(), k) == netstations.end()) { //https://overcoder.net/q/1229580/%D0%BA%D0%B0%D0%BA-%D0%BF%D1%80%D0%BE%D0%B2%D0%B5%D1%80%D0%B8%D1%82%D1%8C-%D1%81%D1%83%D1%89%D0%B5%D1%81%D1%82%D0%B2%D1%83%D0%B5%D1%82-%D0%BB%D0%B8-%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D0%B2%D0%B5%D0%BA%D1%82%D0%BE%D1%80%D0%B5-c-stl-%D0%B8-%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D0%BD%D0%B8%D1%82%D1%8C-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8E-%D0%BA
		std::cout << "\nЭта КС уже в сети\n";
	}
	else {
		netstations.push_back(k);
	}
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
		if (netpipes[i].GetIn().GetId() == k.GetId() || netpipes[i].GetOut().GetId() == k.GetId()) {
			netpipes.erase(netpipes.begin() + i - 1);
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

void network::DelPipe(int widin, int widout)
{
	for (int i = 0; i <= netpipes.size(); i++) {
		if (netpipes[i].GetIn().GetId() == widin && netpipes[i].GetOut().GetId() == widout) {
			netpipes.erase(netpipes.begin() + i - 1);
		}
	}
}

bool network::AreConnected(int widin, int widout)
{
	for (int i = 0; i <= netpipes.size(); i++) {
		if (netpipes[i].GetIn().GetId() == widin && netpipes[i].GetOut().GetId() == widout) {
			return true;
		}
	}
}


