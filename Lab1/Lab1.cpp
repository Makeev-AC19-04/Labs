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

int entintvalue(const char * out) { // Функция корректного ввода целого числа
    int in = 1;
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

void readpipe(pipe p) { // Функция чтения из файла для трубы
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

void readks(ks k) { // Функция чтения из файла для KC
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

void printpipe(pipe p) { // Функция отображения одной трубы
    std::cout << "\nПараметры трубы:\n" << "Длина: " << p.length << "\nДиаметр: " << p.diameter << "\nСтатус в ремонте: " << p.fix << "\nID трубы: " << p.id << "\n";
}

void printks(ks k) { // Функция отображения одной КС
    std::cout << "\nПараметры КС:\n" << "Название: " << k.name << "\nКол-во цехов: " << k.numc << "\nКол-во рабочих цехов: " << k.numcw << "\nКоэф. эффективности: " << k.effective << "\nID KC: " << k.id << "\n";;
}

pipe createpipe(std::vector<pipe> pipes) { // функция создания трубы
    pipe p;
    p.id = pipes.size() + 1;
    int inmenup;
    inmenup = entintvalue("\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n");
    switch (inmenup) {
    case 1: {
        p.length = entfloatvalue("Введите длину, km\n");
        p.diameter = entintvalue("Введите диаметр, mm\n");
        p.fix = 0;
        break;
    }
    default: {
        readpipe(p);
        }
    }
    if (p.diameter <= 0 || p.length <= 0) {
        std::cout << "В файле содержатся некорректные данные\n";
        return p;
    }
    else {
        printpipe(p);
        return p;
    }
};

ks createks(std::vector<ks> kses) {  // функция создания КС
    int inmenup; ks k;
    k.id = kses.size() + 1;
    inmenup = entintvalue("\nКак вы хотите добавить КС?\n1. Ввести вручную\n2. Из файла\n");
    switch (inmenup) {
    case 1: {
            std::cout << "\nВведите название КС\n";
            std::cin.ignore(32767, '\n');
            getline(std::cin, k.name);
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
        readks(k);
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

void loaddata(std::vector<ks> kses, std::vector<pipe> pipes) { // Функция загрузки всех объектов в соовтетствующий массив
    pipe p; ks k;
    int pid = 0, kid = 0;
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

void changepipe(std::vector<pipe> pipes) { // Функция остановки (запуска) цехов
    int wid, inmenu;
    while (1) {
        wid = entintvalue("\nВведите id трубы:\n");
        if (wid <= pipes.size()) {
            break;
        }
    }
    wid--; // Т.к. нумерация в массиве начинается с 0
    printpipe(pipes[wid]);
    std::cout << "\nХотите поменять статус в ремонте?\n1. Да\n2. Нет\n";
    std::cin >> inmenu;
    switch (inmenu) {
    case 1: {
        pipes[wid].fix = !pipes[wid].fix;
        std::cout << "Признак в ремонте изменен на противоположный";
    }
    default: {
        break;
    }
    }
}

void changeks(std::vector<ks> kses) { // Функция изменения статуса "В ремонте"
    int wid;
    while (1) {
        wid = entintvalue("\nВведите id KC:\n");
        if (wid <= kses.size()) {
            break;
        }
    }
    wid--; 
        while (1)
        {
            kses[wid].numcw = entintvalue("\n Введите новое число рабочих цехов\n");
            if (kses[wid].numc - kses[wid].numcw >= 0) {
                break;
            }
        }
};

void showall(std::vector<ks> kses, std::vector<pipe> pipes) { // Отображение всех объектов
    int i;
    for (i = 0; i < pipes.size(); i++) {
        printpipe(pipes[i]);
    }
    for (i = 0; i < kses.size(); i++) {
        printks(kses[i]);
    }
}

void save(std::vector<ks> kses, std::vector<pipe> pipes) { // Функция сохранения всего в файл
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
    int inmenu = 0;
    pipe p;
    ks k;
    std::vector<pipe> pipes; // Массив труб
    std::vector<ks> kses; // Массив станций
    loaddata(kses, pipes);
    while (1) {
        inmenu = entintvalue("\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Запуск/остановка цехов КС\n5. Изменить статус в ремонте для трубы\n6. Сохранить\n 7. Выход\n");
        switch (inmenu) {
        case 1: {
            pipes.push_back(createpipe(pipes)); //добавление трубы
            break;
        }
        case 2: { //добавление КС
            kses.push_back(createks(kses));
            break;
        }
        case 3: { //просмотр всех объектов
            showall(kses, pipes);
            break;
        }
        case 4: { //запуск или остановка цехов КС
            changeks(kses);
            break;
        }
        case 5: {
            changepipe(pipes); //изменить статус "В ремонте" для трубы
            break;
        }
        case 6: { //сохранение в файл
            save(kses, pipes);
            break;
        }
        case 7: { //выход из программы
            return 0;
        }
        }
        }
};