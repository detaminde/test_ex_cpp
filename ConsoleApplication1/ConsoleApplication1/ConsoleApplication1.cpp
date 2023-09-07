#include <iostream>
#include <locale>
#include <vector>
#include <random>
#include <typeinfo>

#include "Fabric.h"

// переопределение операторов вывода для точек и векторов
std::ostream& operator<<(std::ostream& os, const Point3D& p)
{
    return os << "{ " << p.x << ", " << p.y << ", " << p.z << " }";
}

std::ostream& operator<<(std::ostream& os, const Vector3D& v)
{
    return os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
}

#define MIN -10.0
#define MAX 10.0

// перечисление классов фигур
enum curve_type
{
    circle_t,
    ellipse_t,
    helix_t
};

int main()
{
    setlocale(LC_ALL, "ru");

    // создаём фабрики, определенные в файле Fabric.h
    CircleFabric cFabric {};
    EllipseFabric eFabric{};
    HelixFabric hFabric{};

    // создаём первый контейнер, в котором в будущем 
    //  случайно будут создавать объекты от родительского 
    //  класса Curve
    std::vector<std::shared_ptr<Curve>> vec1;
    // установка диапазона для всех фабрик
    cFabric.setDiaposon(MIN, MAX);
    eFabric.setDiaposon(MIN, MAX);
    hFabric.setDiaposon(MIN, MAX);

    // инициализация источника случайных чисел
    std::random_device rd;
    // инициализация 'рандомайзера' целочисленных 
    //  значений для случайного создания фигур
    std::uniform_int_distribution <> randomer {circle_t, helix_t};
    int type{};
    
    // цикл создания фигур
    for (int i = 0; i < 10; i++)
    {
        type = randomer(rd);
        switch (type)
        {
        case circle_t:
        {
            vec1.push_back(cFabric.createCurve());
            break;
        }
        case ellipse_t:
        {
            vec1.push_back(eFabric.createCurve());
            break;
        }
        case helix_t:
        {
            vec1.push_back(hFabric.createCurve());
            break;
        }
        default:
        {
            vec1.push_back(cFabric.createCurve());
            break;
        }
        }
        
    }
    
    // иницилазиция числа параметра t со значением PI
    double t = acos(-1);
    // вывод для 3 задания; 
    // если выводится круг, то выводим его адрес 
    //  и радиус для последующего сравнения со вторым контейнером
    for (int i = 0; i < vec1.size(); i++)
    {
        std::cout << typeid(*vec1.at(i).get()).name() << " ('point') : " << vec1.at(i).get()->curve_point(t / 4)
            << " ('vector') : " << vec1.at(i).get()->curve_vector(t / 4);
        if (typeid(*vec1.at(i).get()).name() == typeid(Circle).name())
        {
            std::cout << " addres: " << vec1.at(i).get() << "   radii: " << std::dynamic_pointer_cast <Circle> (vec1.at(i))->getRadii();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Создаём контейнер только для кругов из первого контейнера
    std::vector <std::shared_ptr<Circle>> vec2;
    // в цикле заполняем только кругами без копирования
    for (int i = 0; i < vec1.size(); i++)
    {
        if (typeid(*vec1.at(i).get()).name() == typeid(Circle).name())
            vec2.emplace_back(std::dynamic_pointer_cast<Circle> (vec1.at(i)));
    }
    //сортируем второй контейнер по возрастанию, используя функцию sort
    std::sort(vec2.begin(), vec2.end(), 
        [](const std::shared_ptr<Circle>& c1, const std::shared_ptr<Circle>& c2) 
        { return  c1.get()->getRadii() < c2.get()->getRadii(); }
    );

    // вывод радиусов и адресов второго контейнера; суммирование радиусов
    double radiiSum{ 0.0 };
    for (int i = 0; i < vec2.size(); i++)
    {
        std::cout << "Circle addresses: " << vec2.at(i).get() << "   radii: " << vec2.at(i).get()->getRadii() << std::endl;
        radiiSum += vec2.at(i).get()->getRadii();
    }
    // вывод суммы радиусов второго контейнера
    std::cout << "total vec2 sum: " << radiiSum << std::endl;
    


    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
