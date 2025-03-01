#include <iostream>
#include <cmath>
class Triangle
{
    private:
    double a,b,c;
    

    public:
        Triangle(double t_a, double t_b, double t_c) : a(t_a), b(t_b), c(t_c)
        {   

            if(!isTriangle() || !isPos())throw std::invalid_argument("невірні вхідні дані.");      
        }

        bool isTriangle()
        {
            return (a + b > c && a + c > b && b + c > a) ? true : false;
        }

        bool isPos()
        {
            return(a > 0 && b > 0 && c > 0)? true : false;
        }

        double getP(){
            if(!isTriangle() || !isPos())throw std::invalid_argument("невірні вхідні дані.");
            return a+b+c;
            }

        double getS()
        {
            double p = getP() / 2.0;         
          if(!isTriangle() || !isPos())throw std::invalid_argument("невірні вхідні дані.");
            
            return sqrt(p*(p - a)*(p-b)*(p-c));
        }
        
        void getA(double t_a){a = t_a;}
         void getB(double t_b){b = t_b;}
         void getC(double t_c) {c = t_c;}

        void print(double getValue){std::cout << getValue << std::endl;}
};
