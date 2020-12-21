#include "network.h"
#include <vector>
#include <iostream>

network::network()
{
}

network::~network()
{
}

void network::SetMatr()
{
	for (int i = 0; i < netstations.size() - 2; i++) {
		for (int j = 0; j < netstations.size() - 2; j++) {
			if (AreConnected(netstations[i].GetId(), netstations[j].GetId()) && i != j) {
				MatrSmej[i][j] = true;
			}
			else
			{
				MatrSmej[i][j] = false;
			}
		}
	}
	PrintMatr();
}

void network::PrintMatr()
{
	for (int i = 0; i < netstations.size(); i++) {
		for (int j = 0; j < netstations.size(); j++) {
			cout << MatrSmej[i][j] << " ";
		}
		cout << endl;
	}
}

void network::SetStations(ks k)
{
	if (netstations.size() == 0) {
		netstations.insert(make_pair(k.GetId(), k));
	}
	else if (std::find(netstations.begin(), netstations.end(), k) == netstations.end()) { //https://overcoder.net/q/1229580/%D0%BA%D0%B0%D0%BA-%D0%BF%D1%80%D0%BE%D0%B2%D0%B5%D1%80%D0%B8%D1%82%D1%8C-%D1%81%D1%83%D1%89%D0%B5%D1%81%D1%82%D0%B2%D1%83%D0%B5%D1%82-%D0%BB%D0%B8-%D0%B7%D0%BD%D0%B0%D1%87%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D0%B2%D0%B5%D0%BA%D1%82%D0%BE%D1%80%D0%B5-c-stl-%D0%B8-%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D0%BD%D0%B8%D1%82%D1%8C-%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8E-%D0%BA
		std::cout << "\nЭта КС уже в сети\n";
	}
	else {
		netstations.insert(make_pair(k.GetId(), k));
	}
}

bool network::CheckKs(int id)  //https://coderoad.ru/1939953/%D0%9A%D0%B0%D0%BA-%D0%BD%D0%B0%D0%B9%D1%82%D0%B8-%D1%81%D1%83%D1%89%D0%B5%D1%81%D1%82%D0%B2%D1%83%D0%B5%D1%82-%D0%BB%D0%B8-%D0%B4%D0%B0%D0%BD%D0%BD%D1%8B%D0%B9-%D0%BA%D0%BB%D1%8E%D1%87-%D0%B2-C-std-map
{
	if (netstations.find(id) == netstations.end()) {
		return false;
	}
	else {
		return true;
	}
}


void network::SetPipes(pipe p)
{
	netpipes.insert(make_pair(p.GetId(), p));
}

bool network::CheckPipe(int id)
{
	if (netpipes.find(id) == netpipes.end()) {
		return false;
	}
	else {
		return true;
	}
}
//
//bool network::AreConnected(int widin, int widout)
//{
//	if (netpipes.size() != 0) {
//		for (int i = 0; i <= netpipes.size() - 1; i++) {
//		    if (netpipes[i].GetIn() == widin && netpipes[i].GetOut() == widout) {
//				return true;
//			}
//		}
//	}
//}

int network::FindKs(int id)
{
    int fid;
    for (int i = 0; i <= netstations.size() - 1; i++) {
        if (netstations[i].GetId() == id) {
            fid = i;
        }
    }
    return fid;
}

void network::SortNet()
{

}

bool network::IsTree()
{
    if (MatrSmej.size() != 0) {
    }
    else {
        return false;
    }
}

void network::change(vector <pipe> pipes, vector <ks> kses)
{
        int inmenu, pid, id, id1, id2;
        cout << "\nЧто вы хотите сделать?\n1. Добавить КС\n2. Соединить 2 КС\n3. Удалить КС\n4. Разорвать связь между КС\n";
        cin >> inmenu;
		switch (inmenu)
		{
		case 1: {
			cout << "\nВведите id КС. После последнего id введите 0\n";
			cin >> id;
			while (1) {
				if (id == 0) {
					break;
				}
				else if (id > pipes.size()) {
					cout << "\nТакой КС нет\n";
				}
				else if (CheckKs(id)) {
					cout << "\nЭта КС уже в сети\n";
				}
				else {
					netstations.insert(make_pair(id, kses[id - 1]));
				}
			}
			break;
		}
		case 2: {
			cout << "\nВведите id трубы\n";
			cin >> pid;
			while (1) {
				if (CheckPipe(pid)) {
					cout << "\nЭта труба уже в сети\n";
				}
				else if (pid > pipes.size()) {
					cout << "\nТакой трубы нет\n";
				}
				else
				{
					netpipes.insert(make_pair(pid, pipes[pid - 1]));
					break;
				}
			}
			cout << "\nВведите id первой КС (источник)\n";
			cin >> id;
			while (1) {
				if (CheckKs(id)) {
					netstations[id].SetOut(netpipes[pid]);
					netpipes[pid].SetIn(netstations[id]);
					break;
				}
				else {
					cout << "\nЭтой КС нет в сети\n";
				}
			}
			cout << "\nВведите id второй КС (сток)\n";
			cin >> id;
			while (1) {
				if (CheckKs(id)) {
					netstations[id].SetIn(netpipes[pid]);
					netpipes[pid].SetOut(netstations[id]);
					break;
				}
				else {
					cout << "\nЭтой КС нет в сети\n";
				}
			}
			break;
		}
		case 3: {
			cout << "\nВведите id станции\n";
			cin >> id;
			while (1)
			{
				if (CheckKs(id)) {
					netstations.erase(id);
					break;
				}
				else {
					cout << "\nЭтой КС нет в сети\n";
				}
			}
			break;
		}
		case 4: {
			while (1) {
				cout << "\nВведите id первой КС\n";
				cin >> id1;
				if (CheckKs(id1)) { break; }
			}
			while (1){
				cout << "\nВведите id второй КС\n";
				cin >> id2;
				if (CheckKs(id2)) { break; }
			}
		}
		}

       
}
