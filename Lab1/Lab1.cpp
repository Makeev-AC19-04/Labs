#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct pipe { //структура трубы
    int id;
    float length;
    int diameter;
    bool fix;
}; 

struct ks {  //структура кс
    int id;
    std::string name;
    int numc;
    int numcw;
    float effective;
}; 

pipe p;
ks k;

std::vector<pipe> pipes; // Массив труб
std::vector<ks> kses; // Массив станций

int entintvalue(const char * out) { // Функция корректного ввода целого числа
    int in;
    do {
        std::cout << out;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> in;
    } while (std::cin.fail() || in <= 0);
    return in;
};

float entfloatvalue(const char* out) { // Функция корректного ввода дробного числа
    float in;
    do {
        std::cout << out;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin >> in;
    } while (std::cin.fail() || in <= 0);
    return in;
};

void readpipe() { // Функция чтения из файла для трубы
    std::ifstream fin;
    fin.open("pipe.txt", std::ios::in);
    if (fin.is_open()) {
        fin >> p.length >> p.diameter >> p.fix;
        fin.close();
    }
    else {
        std::cout << "Ошибка открытия файла";
    }
};

void readks() { // Функция чтения из файла для KC
    std::ifstream fin;
    fin.open("ks.txt", std::ios::in);
    if (fin.is_open()) {
        fin >> k.name >> k.numc >> k.numcw >> k.effective;
        fin.close();
    }
    else {
        std::cout << "Ошибка открытия файла";
    }
}

void printpipe(pipe pp) { // Функция отображения одной трубы
    std::cout << "\nПараметры трубы:\n" << "Длина: " << p.length << "\nДиаметр: " << p.diameter << "\nСтатус в ремонте: " << p.fix << "\nID трубы: " << p.id << "\n";
}

void printks(ks pk) { // Функция отображения одной КС
    std::cout << "\nПараметры КС:\n" << "Название: " << k.name << "\nКол-во цехов: " << k.numc << "\nКол-во рабочих цехов: " << k.numcw << "\nКоэф. эффективности: " << k.effective << "\nID KC: " << k.id << "\n";;
}

pipe createpipe() { // функция создания трубы
    p.id = pipes.size() + 1;
    int inmenup;
    std::cout << "\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n";
    std::cin >> inmenup;
    switch (inmenup) {
    case 1: {
        p.length = entfloatvalue("Введите длину, km\n");
        p.diameter = entintvalue("Введите диаметр, mm\n");
        p.fix = 0;
        break;
    }
    default: {
        readpipe();
        }
    }
    if (p.diameter <= 0 || p.length <= 0) {
        std::cout << "В файле содержатся некорректные данные\n";
        return p;
    }
    else {
        printpipe(p);
        pipes.push_back(p);
        return p;
    }
};

ks createks() {  // функция создания КС
    int inmenup;
    k.id = kses.size() + 1;
    std::cout << "\nКак вы хотите добавить КС?\n1. Ввести вручную\n2. Из файла\n";
    std::cin >> inmenup;
    switch (inmenup) {
    case 1: {
            std::cout << "\nВведите название КС\n";
            std::cin >> k.name;
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
        readks();
        break;
        }
    }
    if (k.numc <= 0 || k.numcw <= 0 || k.effective <= 0 || k.numcw > k.numc) {
        std::cout << "В файле содержатся некорректные данные\n";
        return k;
    }
    else {
        printks(k);
        kses.push_back(k);
        return k;
    }
};

void loaddata() { // Функция загрузки всех объектов в соовтетствующий массив
    int pid = 1, kid = 1;
    std::string currentline;
    std::ifstream fin;
    fin.open("data.txt", std::ios::in);
    if (fin.is_open()) {
        while (getline(fin, currentline)) { //https://ru.stackoverflow.com/questions/258989/%d0%a7%d1%82%d0%b5%d0%bd%d0%b8%d0%b5-%d1%84%d0%b0%d0%b9%d0%bb%d0%b0-%d0%bf%d0%be%d1%81%d1%82%d1%80%d0%be%d1%87%d0%bd%d0%be
            if (currentline == "pipe") {
                fin >> p.length >> p.diameter >> p.fix;
                p.id = pid;
                pipes.push_back(p);
                pid++;
            }
            else if (currentline == "kc") {
                fin >> k.name >> k.numc >> k.numcw >> k.effective;
                k.id = kid;
                kses.push_back(k);
                kid++;
            }
        }
        fin.close();
    }
    else {
        std::cout << "Ошибка открытия файла";
    }
};

void changepipe() { // Функция остановки (запуска) цехов
    int wid, inmenu;
    while (1) {
        wid = entintvalue("\nВведите id трубы:\n");
        if (wid <= pipes.size()) {
            break;
        }
    }
    wid--; // Т.к. нумерация в массиве начинается с 0
    printpipe(pipes[wid]);
    p = pipes[wid];
    std::cout << "\nХотите поменять статус в ремонте?\n1. Да\n2. Нет\n";
    std::cin >> inmenu;
    switch (inmenu) {
    case 1: {
        p.fix = !p.fix;
        std::cout << "Признак в ремонте изменен на противоположный";
        pipes[wid] = p;
    }
    default: {
        break;
    }
    }
}

void changeks() { // Функция изменения статуса "В ремонте"
    int wid, inmenu;
    while (1) {
        wid = entintvalue("\nВведите id KC:\n");
        if (wid <= kses.size()) {
            break;
        }
    }
    wid--; 
    printks(kses[wid]);
    k = kses[wid];
    std::cout << "\nХотите запустить/остановить цеха?\n1. Да\n2. Нет\n";
    std::cin >> inmenu;
    switch (inmenu) {
    case 1: {
        while (1)
        {
            k.numcw = entintvalue("\n Введите новое число рабочих цехов\n");
            if (k.numc - k.numcw >= 0) {
                break;
            }
        }
        kses[wid] = k;
    }
    default: {
        break;
    }
    }
};

void showall() { // Отображение всех объектов
    int i;
    for (i = 0; i < pipes.size(); i++) {
        p = pipes[i];
        printpipe(p);
    }
    for (i = 0; i < kses.size(); i++) {
        k = kses[i];
        printks(k);
    }
}

void loadobject() {
    int inmenu;
    std::cout << "Что вы хотите загрузить?\n1. Трубу\n2. KC\n";
    std::cin >> inmenu;
    switch (inmenu) {
    case 2: {
        changeks();
        break;
    }
    default: {
        changepipe();
        break;
    }
    }
}

void save() { // Функция сохранения всего в файл
    int i;
    std::ofstream fin;
    fin.open("data.txt", std::ios::out);
    for (i = 0; i < pipes.size(); i++) {
        fin << "\n" << "pipe" << "\n" << pipes[i].length << "\n" << pipes[i].diameter << "\n" << pipes[i].fix << "\n" << pipes[i].id << "\n";
    }
    for (i = 0; i < kses.size(); i++) {
        fin << "\n" << "kc\n" << kses[i].name << "\n" << kses[i].effective << "\n" << kses[i].numc << "\n" << kses[i].numcw << "\n" << kses[i].id << "\n";
    }
    fin.close();
    std::cout << "\nДанные сохранены\n";
}

int main()
{
    std::string currentline;
    int inmenu;
    loaddata();
    while (1) {
        inmenu = entintvalue("\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Загрузить и изменить\n5. Сохранить \n6. Выход\n");
        switch (inmenu) {
        case 1: {
            createpipe(); //добавление трубы
            break;
        }
        case 2: { //добавление КС
            createks();
            break;
        }
        case 3: { //просмотр всех объектов
            showall();
            break;
        }
        case 4: { //загрузка и действие с объектом
            loadobject();
            break;
        }
        case 5: {
            save();
            break;
        }
        case 6: { //выход из программы
            return 0;
        }
        }
        }
};