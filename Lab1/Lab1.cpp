

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
    int inmenup;
    //char filename;
    std::cout << "\nКак вы хотите добавить трубу?\n1. Вручную\n2. Из файла\n3. Отмена\n";
    std::cin >> inmenup;
    while (1) {
        if (inmenup == 1) {
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
        else if (inmenup == 2) {
            std::ifstream fin;
            fin.open("pipe.txt", std::ios::in);
            fin >> d.length >> d.diameter >> d.fix >> d.id;
            fin.close();
            break;
        }
        else if (inmenup == 3) {
            std::cout << "\nВыход из добавления трубы\n";
            break;
        }
        return d;
    }
};

    ks createks() {
    ks kc;
    int inmenup;
    kc.id = 0;
    std::cout << "\nКак вы хотите добавить КС?\n1. Ввести вручную\n2. Из файла\n3. Отмена\n";
    std::cin >> inmenup;
    while (1) {
        if (inmenup == 1) {
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
        if (inmenup == 2) {
            std::ifstream fin;
            fin.open("ks.txt", std::ios::in);
            fin >> kc.name >> kc.numc >> kc.numcw >> kc.effective;
            fin.close();
            break;
        }
        if (inmenup == 3) {
            std::cout << "\nВыход из добавления КС\n";
            break;
        }
        return kc;
    }
};

int main()
{
    int inmenu;

    pipe p;
    ks k;
    while (1) {
        std::cout << "\nМеню:\n1. Добавить трубу\n2. Добавить КС\n3. Просмотр всех объектов\n4. Редактировать трубу\n5. Редактировать КС\n6. Сохранить\n7. Загрузить\n0. Выход\n";
        std::cin >> inmenu;
        if (inmenu == 1) {
                while (1) {
                    p = createpipe();
                    std::cout << "\nТекущие параметры трубы:\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id;
                    std::cout << "\nСохранить?\n1.Да\n2.Нет\n";
                    std::cin >> inmenu;
                    if (inmenu == 1) {
                        std::cout << "\nТруба сохранена\n";
                        std::ofstream fin;
                        fin.open("data.txt", std::ofstream::out | std::ofstream::app); //https://coderoad.ru/54498954/%D0%94%D0%BE%D0%B1%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB-%D0%B1%D0%B5%D0%B7-%D1%81%D1%82%D0%B8%D1%80%D0%B0%D0%BD%D0%B8%D1%8F-%D1%82%D0%BE%D0%B3%D0%BE-%D1%87%D1%82%D0%BE-%D0%BD%D0%B0%D1%85%D0%BE%D0%B4%D0%B8%D1%82%D1%81%D1%8F-%D0%B2%D0%BD%D1%83%D1%82%D1%80%D0%B8
                        fin << "\n" << p.length << "\n" << p.diameter << "\n" << p.fix << "\n" << p.id << "\n";
                        fin.close();
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
        else if (inmenu == 2) {
            while (1) {
                k = createks();
                std::cout << "Текущие параметры КС:\n" << k.effective << "\n" << k.id << "\n" << k.name << "\n" << k.numc << "\n" << k.numcw;
                std::cout << "\nСохранить?\n1.Да\n2.Нет\n";
                std::cin >> inmenu;
                if (inmenu == 1) {
                    std::cout << "\nКС сохранена\n";
                    std::ofstream fin;
                    fin.open("data.txt", std::ofstream::out | std::ofstream::app); //https://coderoad.ru/54498954/%D0%94%D0%BE%D0%B1%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5-%D0%B2-%D1%84%D0%B0%D0%B9%D0%BB-%D0%B1%D0%B5%D0%B7-%D1%81%D1%82%D0%B8%D1%80%D0%B0%D0%BD%D0%B8%D1%8F-%D1%82%D0%BE%D0%B3%D0%BE-%D1%87%D1%82%D0%BE-%D0%BD%D0%B0%D1%85%D0%BE%D0%B4%D0%B8%D1%82%D1%81%D1%8F-%D0%B2%D0%BD%D1%83%D1%82%D1%80%D0%B8
                    fin << "\n" << k.name << "\n" << k.effective << "\n" << k.numc << "\n" << k.numcw << "\n" << k.id << "\n";
                    fin.close();
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
