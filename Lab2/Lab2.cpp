#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class pipe //класс трубы
{
public:
    int id;
    float length;
    int diameter;
    bool fix;
};

class ks //класс КС
{
public:
    int id;
    string name;
    int numc;
    int numcw;
    float effective;
};

struct objects {
    vector<pipe> pipes; // Массив труб
    vector<ks> kses; // Массив станций
};

int entintvalue(const string out) { // Функция корректного ввода целого числа
    int in = 1;
    do {
        cout << out;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> in;
    } while (cin.fail() || in <= 0);
    return in;
};

float entfloatvalue(const string out) { // Функция корректного ввода дробного числа
    float in;
    do {
        cout << out;
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> in;
    } while (cin.fail() || in <= 0);
    return in;
};

pipe readpipe(pipe p) { // Функция чтения из файла для трубы
    ifstream fin;
    string file;
    cout << "\nВведите имя файла\n";
    cin >> file;
    fin.open(file, ios::in);
    if (fin.is_open()) {
        fin >> p.length >> p.diameter >> p.fix;
        fin.close();
        return p;
    }
    else {
        cout << "Ошибка открытия файла";
    }
};

ks readks(ks k) { // Функция чтения из файла для KC
    ifstream fin;
    string file;
    cout << "\nВведите имя файла\n";
    cin >> file;
    fin.open(file, ios::in);
    if (fin.is_open()) {
        fin >> k.name >> k.numc >> k.numcw >> k.effective;
        fin.close();
    }
    else {
       cout << "Ошибка открытия файла";
    }
    return k;
}

void printpipe(pipe p) { // Функция отображения одной трубы
    cout << "\nПараметры трубы:\n" << "Длина: " << p.length << "\nДиаметр: " << p.diameter << "\nСтатус в ремонте: " << p.fix << "\nID трубы: " << p.id << "\n";
}

void printks(ks k) { // Функция отображения одной КС
    cout << "\nПараметры КС:\n" << "Название: " << k.name << "\nКол-во цехов: " << k.numc << "\nКол-во рабочих цехов: " << k.numcw << "\nКоэф. эффективности: " << k.effective << "\nID KC: " << k.id << "\n";;
}

pipe createpipe(vector<pipe> pipes) { // функция создания трубы
    pipe p;
    p.id = pipes.size() + 1;
    int inmenup;
    while (1) {
        inmenup = entintvalue("\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n");
        switch (inmenup) {
        case 1: {
            p.length = entfloatvalue("Введите длину, km\n");
            p.diameter = entintvalue("Введите диаметр, mm\n");
            p.fix = 0;
            break;
        }
        default: {
            p = readpipe(p);
        }
        }
        if (p.diameter > 0 || p.length > 0) {
            printpipe(p);
            return p;
            break;
        }
    }
};

ks createks(vector<ks> kses) {  // функция создания КС
    int inmenup; ks k;
    k.id = kses.size() + 1;
    while (1) {
        inmenup = entintvalue("\nКак вы хотите добавить КС?\n1. Ввести вручную\n2. Из файла\n");
        switch (inmenup) {
        case 1: {
            cout << "\nВведите название КС\n";
            cin.ignore(32767, '\n');
            getline(cin, k.name);
            k.numc = entintvalue("Введите кол-во цехов\n");
            while (1) {
                k.numcw = entintvalue("Введите кол-во рабочих цехов\n");
                if (k.numcw <= k.numc) {
                    break;
                }
            }
            k.effective = entfloatvalue("Введите коеф. эффективности\n");
            break;
        }
        default: {
            k = readks(k);
            break;
        }
        }
        if (k.numc > 0 || k.numcw > 0 || k.effective > 0 || k.numcw < k.numc) {
            printks(k);
            kses.push_back(k);
            return k;
        }
    }
};

objects loaddata() { // Функция загрузки всех объектов в соовтетствующий массив
    pipe p; ks k;
    objects data;
    int pid = 1, kid = 1;
    string currentline;
    ifstream fin;
    fin.open("data.txt", ios::in);
    if (fin.is_open()) {
        while (getline(fin, currentline)) { //https://ru.stackoverflow.com/questions/258989/%d0%a7%d1%82%d0%b5%d0%bd%d0%b8%d0%b5-%d1%84%d0%b0%d0%b9%d0%bb%d0%b0-%d0%bf%d0%be%d1%81%d1%82%d1%80%d0%be%d1%87%d0%bd%d0%be
            if (currentline == "pipe") {
                fin >> p.length >> p.diameter >> p.fix;
                p.id = pid;
                data.pipes.push_back(p);
                pid++;
            }
            else if (currentline == "kc") {
                fin >> k.name >> k.numc >> k.numcw >> k.effective;
                k.id = kid;
                data.kses.push_back(k);
                kid++;
            }
        }
        fin.close();
    }
    else {
        cout << "Ошибка открытия файла";
    }
    return data;
};

objects changeonepipe(objects data, int wid, int inmenu, int change) {
    switch (inmenu) {
    case 1: {
        data.pipes[wid].length = change;
        break;
    }
    case 2: {
        data.pipes[wid].diameter = change;
        break;
    }
    default: {
        data.pipes[wid].fix = !data.pipes[wid].fix;
        cout << "Признак в ремонте изменен на противоположный";
        break;
    }
    }
    return data;
}

objects changeoneks(objects data, int wid, int inmenu, int changeint, float changefloat, string changestring){
    switch (inmenu)
    {
    case 1: {
        data.kses[wid].name = changestring;
        break;
    }
    case 2: {
        data.kses[wid].numc = changeint;
        break;
    }
    case 3: {
        while (1)
        {
            data.kses[wid].numcw = changeint;
            if (data.kses[wid].numc - data.kses[wid].numcw >= 0) {
                break;
            }
            else {
                changeint = entintvalue("\nВведите корректное значение\n");
            }
        }
        break;
    }
    default: {
        data.kses[wid].effective = changefloat;
        break;
    }
    }
    return data;
}

objects changesomepipes(objects data, vector <int> ids) {
    int change, inmenu, i;
    inmenu = entintvalue("\nЧто вы хотите поменять?\n1. Длину\n2. Димаетр\n3. Статус в ремонте\n");
    change = entintvalue("\nВведите новое значение\n");
    for (i = 0; i < ids.size(); i++) {
        data = changeonepipe(data, ids[i] - 1, inmenu, change);
    }
    return data;
}

objects changesomekses(objects data, vector <int> ids) {
    int inmenu, changeint = 0, i;
    float changefloat = 0;
    string changestring = "";
    inmenu = entintvalue("Что вы хотите изменить?\n1. Название\n2. Число цехов\n3. Число рабочих цехов\n4. Коеф. эффективности\n");
    switch (inmenu)
    {
    case(1): {
        cout << "\nВведите новое название\n";
        cin >> changestring;
        break;
    }
    case (4): {
        changefloat = entfloatvalue("\nВведите новый коэффициент эффективности\n");
        break;
    }
    default: {
        changeint = entintvalue("\nВведите новое значение\n");
        break;
    }
    }
    for (i = 0; i < ids.size(); i++) {
        data = changeoneks(data, ids[i] - 1, inmenu, changeint, changefloat, changestring);
    }
    return data;
}

objects changepipe(objects data) { // Функция редактирования труб
    int wid, inmenu, change, i = 0;
    vector <int> ids;
    cout << "\nВведите id трубы. После последнего id введите 0\n";
    while (1) {
        cin >> wid;
        if (wid == 0 && ids.size() != 0) {
            break;
        }
        else if (wid <= data.pipes.size() && wid > 0) {
            ids.push_back(wid);
            printpipe(data.pipes[wid-1]);
        }
        else {
            cout << "\nid " << wid << " нет\n";
        }
    }
    data = changesomepipes(data, ids);
    return data;
}

objects changeks(objects data) { // Функция изменения статуса "В ремонте"
    int wid, inmenu, changeint = 0, i;
    float changefloat = 0;
    string changestring = "";
    vector <int> ids;
    cout << "\nВведите id KC. После последнего id введите 0\n";
    while (1) {
        cin >> wid;
        if (wid == 0) {
            break;
        }
        else if (wid <= data.kses.size() && wid > 0) {
            ids.push_back(wid);
            printks(data.kses[wid-1]);
        }
        else {
            cout << "\nid " << wid << " нет\n";
        }
        }
    data = changesomekses(data, ids);
    return data;
};

void showall(objects data) { // Отображение всех объектов
    int i;
    for (i = 0; i < data.pipes.size(); i++) {
        data.pipes[i].id = i + 1;
        printpipe(data.pipes[i]);
    }
    for (i = 0; i < data.kses.size(); i++) {
        data.kses[i].id = i + 1;
        printks(data.kses[i]);
    }
}

void save(objects data) { // Функция сохранения всего в файл
    int i;
    ofstream fin;
    string file;
    cout << "\nВведите имя файла для сохранения\n";
    cin >> file;
    fin.open(file, ios::out);
    if (fin.is_open()) {
        for (i = 0; i < data.pipes.size(); i++) {
            fin << "\n" << "pipe" << "\n" << data.pipes[i].length << "\n" << data.pipes[i].diameter << "\n" << data.pipes[i].fix << "\n" << data.pipes[i].id << "\n";
        }
        for (i = 0; i < data.kses.size(); i++) {
            fin << "\n" << "kc\n" << data.kses[i].name << "\n" << data.kses[i].effective << "\n" << data.kses[i].numc << "\n" << data.kses[i].numcw << "\n" << data.kses[i].id << "\n";
        }
        fin.close();
        cout << "\nДанные сохранены\n";
    }
    else {
        cout << "Ошибка открытия файла";
    }
}

objects deleteobject(objects data) {
    int inmenu, wid;
    inmenu = entintvalue("Что вы хотите удалить?\n1. Трубу\n2. KC\n");
    switch (inmenu)
    {
    case 1: {
        while (1) {
            wid = entintvalue("\nВведите id трубы:\n");
            if (wid <= data.pipes.size()) {
                break;
            }
        }  
        data.pipes.erase(data.pipes.begin() + wid - 1);
        break;
    }
    default: {
        while (1) {
            wid = entintvalue("\nВведите id KC:\n");
            if (wid <= data.kses.size()) {
                break;
            }
        }
        data.kses.erase(data.kses.begin() + wid - 1);
        break;
    }
    }
    cout << "\nОбъект удален\n";
    return data;
}

objects searchpipe(objects data) {
    bool fix;
    int i, inmenu;
    vector <int> ids;
    while (1) {
        cout << "\nВведите признак в ремонте (1 или 0)\n";
        cin >> i;
        if (i == 1 || i == 0) {
            break;
        }
    }
    if (i == 1) {
        fix = 1;
    }
    else {
        fix = 0;
    }
    for (i = 0; i < data.pipes.size(); i++) {
        if (data.pipes[i].fix == fix) {
            printpipe(data.pipes[i]);
            ids.push_back(i);
        }
    }
    inmenu = entintvalue("\nВы хотите изменить эти объекты?\n1. Да\n2. Нет\n");
    switch (inmenu) {
    case(1): {
        data = changesomepipes(data, ids);
    }
    default: {
        break;
    }
    }
    return data;
}

objects searchks(objects data) {
    string name;
    float minpercent, maxpercent, percent;
    int i, inmenu;
    vector <int> ids;
    cout << "\nВведите название KC\n";
    cin >> name;
    minpercent = entfloatvalue("Введите процент незадействованных цехов, нижний предел\n") / 100;
    maxpercent = entfloatvalue("Введите процент незадействованных цехов, верхний предел\n") / 100;
    for (i = 0; i < data.kses.size(); i++) {
        percent = (data.kses[i].numc - data.kses[i].numcw + 0.0) / data.kses[i].numc; //+0.0 т.к. без этого отбрасывается остаток
        if (data.kses[i].name == name && (((percent <= maxpercent) && ((percent >= minpercent))))) {
            printks(data.kses[i]);
            ids.push_back(i);
        }
    }
    inmenu = entintvalue("\nХотите изменить эти объекты?\n1. Да\n2.Нет\n");
    switch (inmenu){
    case(1): {
        data = changesomekses(data, ids);
        }
    default: {
        break;
    }
    }
    return data;
}

objects search(objects data) {
    int inmenu, i;
    inmenu = entintvalue("\nЧто вы хотите найти?\n1.Трубу\n2. KC\n");
    switch (inmenu)
    {
    case 1: {
        data = searchpipe(data);
        break;
    }
    default:
        data = searchks(data);
        break;
    }
    return data;
}

int main()
{
    string currentline;
    int inmenu = 0;
    objects data;
    data = loaddata();
    while (1) {
        inmenu = entintvalue("\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать КС\n5. Редактировать трубу(-ы)\n6. Удалить объект\n7. Поиск объектов\n8. Сохранить\n9. Выход\n");
        switch (inmenu) {
        case 1: {
            data.pipes.push_back(createpipe(data.pipes)); //добавление трубы
            break;
        }
        case 2: { //добавление КС
            data.kses.push_back(createks(data.kses));
            break;
        }
        case 3: { //просмотр всех объектов
            showall(data);
            break;
        }
        case 4: { //Редактирование КС
            data = changeks(data);
            break;
        }
        case 5: {
            data = changepipe(data); //Редактирование трубы
            break;
        }
        case 6: {
            data = deleteobject(data); //удаление объекта
            break;
        }
        case 7: {
            data = search(data); //Поиск объектов по фильтру
            break;
        }
        case 8: { //сохранение в файл
            save(data);
            break;
        }
        case 9: { //выход из программы
            return 0;
        }
        }
    }
};