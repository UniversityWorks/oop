#include "class.hpp" 

int main()
{
    std::cout << "Введіть сторони трикутника" << std::endl;
    double a,b,c;
    std::cin >> a >> b >> c;

    Triangle triangle(a,b,c);

    triangle.print(triangle.getP());
    triangle.print(triangle.getS());


    
    
    return 0;
}