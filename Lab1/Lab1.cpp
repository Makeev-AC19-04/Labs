

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
    int fx;
    d.id = 0;
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
    bool menu1;
    while (1) {
        std::cout << "\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n";
        std::cin >> inmenu;
        if (inmenu == 1) {
            menu1 = true;
            std::cout << "\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n3. Отмена\n";
            std::cin >> inmenu;
            while (menu1 == true) {
                if (inmenu == 1) {
                    p = createpipe();
                }
                else if (inmenu == 2) {
                    std::cout << "\nВвод из файла\n";
                }
                else if (inmenu == 3) {
                    std::cout << "\nВыход из добавления трубы\n";
                    break;
                }
                while (1) {
                    std::cout << "\nТекущие параметры трубы:\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id;
                    std::cout << "\nСохранить?\n1.Да\n2.Нет\n";
                    std::cin >> inmenu;
                    if (inmenu == 1) {
                        std::cout << "\nТруба сохранена\n";
                        //Запись в файл или еще куда
                        menu1 = false;
                        break;
                    }
                    if (inmenu == 2) {
                        std::cout << "\nЧто вы хотите исправить?\n1. Длину\n2. Диаметр\n3. Признак в ремонте\n4. Удалить трубу\n";
                        std::cin >> inmenu;
                        if (inmenu == 1) {
                            while (1) {
                                std::cout << "Введите новое значение длины\n";
                                std::cin >> p.length;
                                if (p.length <= 0) {
                                    std::cout << "Введите значение больше нуля\n";
                                }
                                else {
                                    break;
                                }
                            }
                        }
                        else if (inmenu == 2) {
                            while (1) {
                                std::cout << "Введите новое значение диаметра\n";
                                std::cin >> p.diameter;
                                if (p.diameter <= 0) {
                                    std::cout << "Введите значение больше нуля\n";
                                }
                                else {
                                    break;
                                }
                            }
                        }
                        else if (inmenu == 3) {
                            p.fix = !p.fix;
                            std::cout << "Признак ремонта изменен на противоположный\n";
                        }
                        else if (inmenu == 4) {
                            std::cout << "Труба удалена\n";
                            menu1 = false;
                            break;
                        }
                    }
                }

            }
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
    }

};
