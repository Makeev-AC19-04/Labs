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

struct objects {
    std::vector<pipe> pipes; // Массив труб
    std::vector<ks> kses; // Массив станций
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

objects loaddata() { // Функция загрузки всех объектов в соовтетствующий массив
    pipe p; ks k;
    objects data;
    int pid = 1, kid = 1;
    std::string currentline;
    std::ifstream fin;
    fin.open("data.txt", std::ios::in);
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
        std::cout << "Ошибка открытия файла";
    }
    return data;
};

objects changepipe(objects data) { // Функция остановки (запуска) цехов
    int wid, inmenu;
    while (1) {
        wid = entintvalue("\nВведите id трубы:\n");
        if (wid <= data.pipes.size()) {
            break;
        }
    }
    wid--; // Т.к. нумерация в массиве начинается с 0
    printpipe(data.pipes[wid]);
    std::cout << "\nХотите поменять статус в ремонте?\n1. Да\n2. Нет\n";
    std::cin >> inmenu;
    switch (inmenu) {
    case 1: {
        data.pipes[wid].fix = !data.pipes[wid].fix;
        std::cout << "Признак в ремонте изменен на противоположный";
    }
    default: {
        break;
    }
    }
    return data;
}

objects changeks(objects data) { // Функция изменения статуса "В ремонте"
    int wid;
    while (1) {
        wid = entintvalue("\nВведите id KC:\n");
        if (wid <= data.kses.size()) {
            break;
        }
    }
    wid--; 
        while (1)
        {
            data.kses[wid].numcw = entintvalue("\n Введите новое число рабочих цехов\n");
            if (data.kses[wid].numc - data.kses[wid].numcw >= 0) {
                break;
            }
        }
        return data;
};

void showall(objects data) { // Отображение всех объектов
    int i;
    for (i = 0; i < data.pipes.size(); i++) {
        printpipe(data.pipes[i]);
    }
    for (i = 0; i < data.kses.size(); i++) {
        printks(data.kses[i]);
    }
}

void save(objects data) { // Функция сохранения всего в файл
    int i;
    std::ofstream fin;
    fin.open("data.txt", std::ios::out);
    for (i = 0; i < data.pipes.size(); i++) {
        fin << "\n" << "pipe" << "\n" << data.pipes[i].length << "\n" << data.pipes[i].diameter << "\n" << data.pipes[i].fix << "\n" << data.pipes[i].id << "\n";
    }
    for (i = 0; i < data.kses.size(); i++) {
        fin << "\n" << "kc\n" << data.kses[i].name << "\n" << data.kses[i].effective << "\n" << data.kses[i].numc << "\n" << data.kses[i].numcw << "\n" << data.kses[i].id << "\n";
    }
    fin.close();
    std::cout << "\nДанные сохранены\n";
}

int main()
{
    std::string currentline;
    int inmenu = 0;
    objects data;
    data = loaddata();
    while (1) {
        inmenu = entintvalue("\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Запуск/остановка цехов КС\n5. Изменить статус в ремонте для трубы\n6. Сохранить\n7. Выход\n");
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
        case 4: { //запуск или остановка цехов КС
            data = changeks(data);
            break;
        }
        case 5: {
            data = changepipe(data); //изменить статус "В ремонте" для трубы
            break;
        }
        case 6: { //сохранение в файл
            save(data);
            break;
        }
        case 7: { //выход из программы
            return 0;
        }
        }
        }
};