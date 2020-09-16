

#include <iostream>
#include <string>

struct pipe {
    int id;
    float length;
    float diameter;
    bool fix;
};

struct ks {
    int id;
    char name;
    int numc;
    int numcw;
    float effective;
};

pipe createpipe() {
    pipe d;
    d.id = 0;
    d.fix = false;
    std::cout << "Введите длину\n";
    std::cin >> d.length;
    std::cout << "Введите диаметр\n";
    std::cin >> d.diameter;
    return d;
};

ks createks() {
    ks kc;
    kc.id = 0;
    std::cout << "Введите название КС\n";
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
    pipe p;
    std::cout << "Hello world!\n";
    p = createpipe();
};
