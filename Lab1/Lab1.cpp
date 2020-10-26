

#include <iostream>
#include <string>
#include <fstream>


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

pipe createpipe() { //функция создания трубы
    pipe d;
    int fx;
    d.id = rand() % 1000000; // исправить
    int inmenup;
    //char filename;
    std::cout << "\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n3. Отмена\n";
    std::cin >> inmenup;
    switch (inmenup) {
    case 1: {
            while (1) {
                std::cout << "Введите длину, km\n";
                std::cin >> d.length;
                if (d.length <= 0) {
                    std::cout << "Введите значение больше нуля\n";
                }
                else {
                    break;
                }
            }
            while (1) {
                std::cout << "Введите диаметр, mm\n";
                std::cin >> d.diameter;
                if (d.diameter <= 0) {
                    std::cout << "Введите значение больше нуля\n";
                }
                else {
                    break;
                }
            }
            std::cout << "Укажите признак в ремонте (1 или 0)\n";
            std::cin >> fx;
            if (fx == 1) {
                d.fix = true;
            }
            else {
                d.fix = false;
            }
        }
    case 2: {
            std::ifstream fin;
            fin.open("pipe.txt", std::ios::in);
            if (fin.is_open()) {
                fin >> d.length >> d.diameter >> d.fix >> d.id;
                fin.close();
            }
            else {
                std::cout << "Ошибка открытия файла";
            }
            break;
        }
    default: {
            std::cout << "\nВыход из добавления трубы\n";
            break;
        }
        return d;
    }
};

ks createks() {  //функция создания КС
    ks kc;
    int inmenup;
    kc.id = rand() % 1000000;;
    std::cout << "\nКак вы хотите добавить КС?\n1. Ввести вручную\n2. Из файла\n3. Отмена\n";
    std::cin >> inmenup;
    switch (inmenup) {
    case 1: {
            std::cout << "\nВведите название КС\n";
            std::cin >> kc.name;
            while (1) {
                std::cout << "Введите кол-во цехов\n";
                std::cin >> kc.numc;
                if (kc.numc <= 0) {
                    std::cout << "Введите значение больше нуля\n";
                }
                else {
                    break;
                }
            }
            while (1) {
                std::cout << "Введите кол-во рабочих цехов\n";
                std::cin >> kc.numcw;
                if (kc.numcw <= 0) {
                    std::cout << "Введите значение больше нуля\n";
                }
                else if (kc.numcw > kc.numc) {
                    std::cout << "Рабочих цехов не может быть больше общего кол-ва\n";
                }
                else {
                    break;
                }
            }
            while (1) {
                std::cout << "Введите коеф. эффективности\n";
                std::cin >> kc.effective;
                if (kc.effective <= 0) {
                    std::cout << "Введите значение больше нуля\n";
                }
                else {
                    break;
                }
            }
        }
    case 2: {
            std::ifstream fin;
            fin.open("ks.txt", std::ios::in);
            if (fin.is_open()) {
                fin >> kc.name >> kc.numc >> kc.numcw >> kc.effective;
                fin.close();
            }
            else {
                std::cout << "Ошибка открытия файла";
            }
            break;
        }
    default: {
            std::cout << "\nВыход из добавления КС\n";
            break;
        }
        return kc;
    }
};

int main()
{
    int inmenu, lastpid, lastksid, wid, i;
    int c = 0;
    std::string currentline;
    pipe p;
    ks k;
    while (1) {
        std::cout << "\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Загрузить\n0. Выход\n"; //вывод меню
        std::cin >> inmenu;
        switch (inmenu) {
        case 1: { //добавление трубы
            while (1) {
                p = createpipe();
                std::cout << "\nТекущие параметры трубы:\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id;
                std::cout << "\nСохранить?\n1.Да\n2.Нет\n";
                std::cin >> inmenu;
                if (inmenu == 1) {
                    std::ofstream fin;
                    fin.open("data.txt", std::ofstream::out | std::ofstream::app); //https://coderoad.ru/54498954/%D0%94%D0%BE%D0%B1%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB-%D0%B1%D0%B5%D0%B7-%D1%81%D1%82%D0%B8%D1%80%D0%B0%D0%BD%D0%B8%D1%8F-%D1%82%D0%BE%D0%B3%D0%BE-%D1%87%D1%82%D0%BE-%D0%BD%D0%B0%D1%85%D0%BE%D0%B4%D0%B8%D1%82%D1%81%D1%8F-%D0%B2%D0%BD%D1%83%D1%82%D1%80%D0%B8
                    if (fin.is_open()) {
                        std::cout << "\nТруба сохранена\n";
                        fin << "\n" << "pipe" << "\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id << "\n";
                        fin.close();
                    }
                    else {
                        std::cout << "Ошибка открытия файла";
                    }
                    break;
                }
                if (inmenu == 2) {
                    std::cout << "\nЧто вы хотите сделать?\n1. Изменить признак в ремонте\n2. Удалить трубу\n";
                    std::cin >> inmenu;
                    if (inmenu == 1)
                    {
                        p.fix = !p.fix;
                        std::cout << "Признак ремонта изменен на противоположный\n";
                        break;
                    }
                    else if (inmenu == 2) {
                        std::cout << "Труба удалена\n";
                        break;
                    }
                }
            }

        }
        case 2: { //добавление КС
            while (1) {
                k = createks();
                std::cout << "Текущие параметры КС:\n" << k.effective << "\n" << k.id << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw;
                std::cout << "\nСохранить?\n1.Да\n2.Нет\n";
                std::cin >> inmenu;
                if (inmenu == 1) {
                    std::ofstream fin;
                    fin.open("data.txt", std::ofstream::out | std::ofstream::app); //https://coderoad.ru/54498954/%D0%94%D0%BE%D0%B1%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB-%D0%B1%D0%B5%D0%B7-%D1%81%D1%82%D0%B8%D1%80%D0%B0%D0%BD%D0%B8%D1%8F-%D1%82%D0%BE%D0%B3%D0%BE-%D1%87%D1%82%D0%BE-%D0%BD%D0%B0%D1%85%D0%BE%D0%B4%D0%B8%D1%82%D1%81%D1%8F-%D0%B2%D0%BD%D1%83%D1%82%D1%80%D0%B8
                    if (fin.is_open()) {
                        std::cout << "\nКС сохранена\n";
                        fin << "\n" << "kc\n" << k.name << "\n" << k.effective << "\n" << k.numc << "\n" << k.numcw << "\n" << k.id << "\n";
                        fin.close();
                    }
                    else {
                        std::cout << "Ошибка сохранения";
                    }
                    break;
                }
                else if (inmenu == 2) {
                    std::cout << "\n" << "Что вы хотите сделать?" << "\n" << "1. Изменить число рабочих станций" << "\n" << "2. Удалить КС" << "\n";
                    std::cin >> inmenu;
                    if (inmenu == 1)
                    {
                        std::cout << "\n Введите новое число рабочих станций\n";
                        while (1)
                        {
                            std::cin >> k.numcw;
                            if (k.numc - k.numcw < 0) {
                                std::cout << "\nРабочих станций не может быть больше общего кол-ва, введите подходящее значение\n";
                            }
                            else {
                                break;
                            }
                        }
                    }
                    else if (inmenu == 2) {
                        std::cout << "КС удалена\n";
                        break;
                    }
                }
            }
        }
        case 3: { //просмотр всех объектов
            std::ifstream fin;
            fin.open("data.txt", std::ios::in);
            std::cout << "Трубы:\n";
            while (getline(fin, currentline)) { //https://ru.stackoverflow.com/questions/258989/%d0%a7%d1%82%d0%b5%d0%bd%d0%b8%d0%b5-%d1%84%d0%b0%d0%b9%d0%bb%d0%b0-%d0%bf%d0%be%d1%81%d1%82%d1%80%d0%be%d1%87%d0%bd%d0%be
                if (currentline == "pipe") {
                    fin >> p.length >> p.diameter >> p.fix >> p.id;
                    std::cout << "\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id << "\n";
                }
            }
            fin.close();
            fin.open("data.txt", std::ios::in);
            std::cout << "\nСтанции:\n";
            while (getline(fin, currentline)) {
                if (currentline == "kc") {
                    fin >> k.name >> k.numc >> k.numcw >> k.effective >> k.id;
                    std::cout << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw << "\n" << k.effective << "\n" << k.id << "\n";
                }
            }
            fin.close();
            //std::cout << c;
        }
        case 4: { //загрузка и действие с объектом
            std::ifstream fin;
            std::cout << "Что вы хотите загрузить?\n1. Трубу\n2. KC\n";
            std::cin >> inmenu;
            if (inmenu == 2) {
                std::cout << "\nВведите id KC:\n";
                std::cin >> wid;
                std::ifstream fin;
                fin.open("data.txt", std::ios::in);
                while (getline(fin, currentline)) {
                    c = c + 1;
                    if (currentline == "kc") {
                        fin >> k.name >> k.numc >> k.numcw >> k.effective >> k.id;
                        if (wid == k.id) {
                            std::cout << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw << "\n" << k.effective << "\n" << k.id << "\n";
                        }
                    }
                }
                std::cout << c;
                std::cout << "\nХотите запустить/остановить цеха?\n1. Да\n2. Нет\n";
                std::cin >> inmenu;
                fin.close();
                if (inmenu == 1) {
                    std::cout << "\n Введите новое число рабочих станций\n";
                    while (1)
                    {
                        std::cin >> k.numcw;
                        if (k.numc - k.numcw < 0) {
                            std::cout << "\nРабочих станций не может быть больше общего кол-ва, введите подходящее значение\n";
                        }
                        else {
                            break;
                        }
                    }
                    //fin.open("data.txt", std::ios::in);
                    for (i = 1; i <= c + 3; ++i) {
                        getline(fin, currentline);
                        //std::cout << "\n" << i << "\n"; //- проверка цикла
                        std::cout << currentline;
                    }
                    std::cout << "Данные  сохранены";
                    fin.close();
                }
            }
            else {
                std::cout << "\nВведите id трубы:\n";
                std::cin >> wid;
                std::ifstream fin;
                fin.open("data.txt", std::ios::in);
                while (getline(fin, currentline)) {
                    if (currentline == "pipe") {
                        fin >> p.length >> p.diameter >> p.fix >> p.id;
                        if (wid == p.id) {
                            std::cout << "\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id << "\n";
                        }
                    }
                }
                std::cout << "\nХотите поменять статус в ремонте?\n1. Да\n2. Нет\n";
                std::cin >> inmenu;
                if (inmenu == 1) {
                    p.fix = !p.fix;
                    std::cout << "Признак в ремонте изменен на противоположный";
                }
            }
        }
        case 0: {
            return 0;
        }
        default: {
            std::cout << "Нет такого пункта меню";
        }
        }
    }

};
