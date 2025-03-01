#include <iostream>
#include "ArithmeticProgression.cpp"
#include "TDisk.cpp"


int main() {
    std::cout << "Завдання 1." << std::endl;
    std::cout << "Прогрессія:" << std::endl;
    Progression progression(1, 2); 
    progression.out();
    std::cout << " Третій елемент: " << progression.getElement(3) << std::endl;
    std::cout << "Сума перших п'яти елементів: " << progression.sum(5) << std::endl;
    std::cout << std::endl;


    std::cout << "Завдання 2." << std::endl;
    std::cout << "Коло TDisk:" << std::endl;
    TDisk disk(5, 0, 0); 
    disk.out();
    std::cout << "Площа круга: " << disk.area() << std::endl;
    std::cout << "Точка (3, 4), належить колу: " << (disk.contains(3, 4) ? "Y" : "N") << std::endl;
    std::cout << std::endl;

    std::cout << "Куля TBall:" << std::endl;
    TBall ball(5, 0, 0, 0);  
    ball.out();
    std::cout << "об`єм кулі: " << ball.volume() << std::endl;
    return 0;
}
