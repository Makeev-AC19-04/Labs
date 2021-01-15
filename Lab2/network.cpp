#include "network.h"
#include <iostream>
#include <fstream>

void network::SetStations(ks  k)
{
	stations.insert(make_pair(k.GetId(), k));
}

void network::SetMapStations(map<int, ks> kses)
{
	stations = kses;
}

map<int, ks> network::GetMapStations()
{
	return stations;
}

bool network::CheckStations(ks k)
{
	if (stations.find(k.GetId()) == stations.end()) { //https://coderoad.ru/1939953/%D0%9A%D0%B0%D0%BA-%D0%BD%D0%B0%D0%B9%D1%82%D0%B8-%D1%81%D1%83%D1%89%D0%B5%D1%81%D1%82%D0%B2%D1%83%D0%B5%D1%82-%D0%BB%D0%B8-%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%B9-%D0%BA%D0%BB%D1%8E%D1%87-%D0%B2-C-std-map
		return false; //Не в КС
	}
	else {
		return true; //В КС
	}
}

bool network::CheckPipes(pipe p)
{
	if (pipes.find(p.GetId()) == pipes.end()) {
		return false; 
	}
	else {
		return true; 
	}
}

void network::PrintWebKses()
{
	std::cout << "\nid КС" << "\t\t" << "id исход. трубы" << "\t\t" << "id вход. трубы\n";
	for (auto& ks : stations) { //https://ru.stackoverflow.com/questions/415336/c-stdmap-%D0%BF%D0%B5%D1%80%D0%B5%D0%B1%D1%80%D0%B0%D1%82%D1%8C-%D0%B2%D1%81%D0%B5-%D1%8D%D0%BB%D0%B5%D0%BC%D0%B5%D0%BD%D1%82%D1%8B
		std::cout << ks.first << "\t\t" << stations[ks.first].AllOuts() << "\t\t\t" << stations[ks.first].AllIns() << endl;
	}
}

void network::SetPipes(pipe p)
{
	pipes.insert(make_pair(p.GetId(), p));
}

void network::SetKsIn(int id, pipe p)
{
	stations[id].SetIn(p.GetId());
}

void network::SetKsOut(int id, pipe p)
{
	stations[id].SetOut(p.GetId());
}

void network::DelKs(int id)
{
	int i = 1;
	if (stations[id].GetIn().size() != 0) {
		for (i = 0; i < stations[id].GetIn().size(); i++) {
			DelPipe(pipes[stations[id].GetIn()[i]].GetId());
		}
	}
	if (stations[id].GetOut().size() != 0) {
		for (i = 0; i < stations[id].GetOut().size(); i++) {
			DelPipe(pipes[stations[id].GetOut()[i]].GetId());
		}
	}
	stations.erase(id);
}

void network::DelPipe(int id) //проверка на наличие трубы
{
	//if (CheckPipes())
	for (auto& ks : stations) {
		stations[ks.first].TruDelOut(id);
		stations[ks.first].TryDelIn(id);
	}
	pipes.erase(id);
}

void network::LoadNet()
{
	ifstream f;
	string currentline, name, in, out;
	ks k;
	pipe p;
	float length, effective;
	bool fix;
	int pid = 1, kid = 1, diameter, numc, numcw;
	f.open("network.txt", ios::in);
	if (f.is_open()) {
		while (getline(f, currentline)) {
			if (currentline == "pipe") {
				f >> length >> diameter >> fix >> pid;
				p.SetLength(length);
				p.SetDiameter(diameter);
				p.SetFix(fix);
				p.SetId(pid);
				pipes.insert(make_pair(pid, p));
			}
			else if (currentline == "kc") {
				f >> name >> effective >> numc >> numcw >> kid  >> in >> out;
				k.SetName(name);
				k.SetNumc(numc);
				k.SetNumcw(numcw);
				k.SetEffective(effective);
				k.SetId(kid);
				k.ReadIns(in);
				k.ReadOuts(out);
				stations.insert(make_pair(kid, k));
				k.ClearPipes();
			}
		}
		f.close();
	}
	else {
		cout << "\nОшибка открытия файла\n";
	}

}

void network::SaveNet()
{
	ofstream f;
	f.open("network.txt", ios::out);
	if (f.is_open()) {
		for (auto& k : stations) {
			f << "\n" << "kc" << "\n" << stations[k.first].GetName() << "\n" << stations[k.first].GetEffective() << "\n" << stations[k.first].GetNumc() << "\n" << stations[k.first].GetNumcw() << "\n" << k.first << "\n" << stations[k.first].AllIns() << "\n" << stations[k.first].AllOuts() << "\n" << endl;
		}
		for (auto& p : pipes) {
			f << "\n" << "pipe" << "\n" << pipes[p.first].GetLength() << "\n" << pipes[p.first].GetDiameter() << "\n" << pipes[p.first].GetFix() << "\n" << p.first << endl;
		}
		cout << "\nСеть сохранена\n";
	}
	else {
		cout << "\nОшибка открытия файла\n";
	}
}

bool network::checksort() {
	bool check = true;
	vector <ks> cycle;
	for (auto& ks : stations) {
		if (ks.second.GetIn().size() >= 3) {
			cout << "\nЭтот граф содержит цикл, его нельзя отсортировать\n";
			check = false;
		}
		else if (ks.second.GetIn().size() == 1 && ks.second.GetOut().size() == 1) {
			cout << "\nГраф содержит изолированную вершину, сортировка невозможна\n";
			check = false;
		}

		else if (ks.second.GetIn().size() == 1) {
			cycle.push_back(ks.second);
		}
	}
	if (cycle.size() == 0) {
		cout << "\nЭтот граф содержит цикл, его нельзя отсортировать\n";
		check = false;
	}
	return check;
}

void network::sort()
{
	network ns;
	ns.SetMapStations(stations);
	vector <int> kvsorted;
	int begin = 1;
	if (checksort()) {
		kvsorted = dosort(ns);
		cout << "№ вершины\t" << "Id KC\n";
		for (int i = 0; i < kvsorted.size(); i++) {
			cout << i + 1 << "\t\t" << kvsorted[i] << "\n";
		}
	}
}

vector<int> network::dosort(network& ns)
{
	vector <int> kvsorted;
	for (auto& k : ns.GetMapStations()) {
		if (ns.GetMapStations().size() == 1) {
			kvsorted.push_back(k.second.GetId());
		}
		if (k.second.GetIn().size() == 1 && k.second.GetOut().size() != 1) {
			kvsorted.push_back(k.second.GetId());
			ns.DelKs(k.second.GetId());
		}
	}
	for (auto& k : ns.GetMapStations()) {
		kvsorted.push_back(k.second.GetId());
		ns.DelKs(k.second.GetId());
	}
	return kvsorted;
}