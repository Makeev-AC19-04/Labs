

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

struct pipe {
    int id;
    float length;
    float diameter;
    bool fix;
};

struct ks {
    int id;
    std::string name;
    int numc;
    int numcw;
    float effective;
};

pipe createpipe() {
    pipe d;
    d.id = 0;
    d.fix = false;
    std::cout << "Введите длину, km\n";
    std::cin >> d.length;
    std::cout << "Введите диаметр, mm\n";
    std::cin >> d.diameter;
    return d;
};

ks createks() {
    ks kc;
    kc.id = 0;
    std::cout << "\nВведите название КС\n";
    std::cin >> kc.name;
    std::cout << "Введите кол-во цехов\n";
    std::cin >> kc.numc;
    std::cout << "Введите кол-во рабочих цехов\n";
    std::cin >> kc.numcw;
    std::cout << "Введите коеф. эффективности\n";
    std::cin >> kc.effective;
    return kc;
};

int main()
{
    int inmenu;
    pipe p;
    ks k;
    std::cout << "Меню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n";
    std::cin >> inmenu;
    if (inmenu == 1) {
        p = createpipe();
        std::cout << "Вы ввели:\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id;
    }
    else if (inmenu == 2) {
        k = createks();
        std::cout << "Вы ввели:\n" << k.effective << "\n" << k.id << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw;
    }
    else if (inmenu == 3) {
    }
    else if (inmenu == 4) {
    }
    else if (inmenu == 5) {
    }
    else if (inmenu == 6) {
    }
    else if (inmenu == 7) {
        //std::ofstream fin;
        //fin.open("C:\\Users\\wane2\\Documents\\Задания\\Алгоритмические языки\\Labs\\Lab1\\data.txt");
        //fin << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id << "\n" << k.effective << "\n" << k.id << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw;
        //fin.close();
    }
    else if (inmenu == 0) {
        return 0;
    }
    else {
        std::cout << "Нет такого пункта меню";
    }

};
