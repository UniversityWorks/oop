#include <iostream>

class Progression
{
    private:
        double first_term;
        double common_difference;

    public:
        Progression() : first_term(0), common_difference(1) {}

        Progression(double first_term_, double common_difference_) : 
        first_term(first_term_), common_difference(common_difference_){} 


        double getElement(int i) const 
        {
            return first_term + (i - 1) * common_difference;
        }


        double sum(int n) const
        {
            return (n / 2.0) * (2 * first_term + (n - 1) * common_difference);
        }

        void in()
        {
            std::cout << "Введіть перший елемент та різницю прогрессії: ";
            std::cin >> first_term >> common_difference;
        }

        void out() const
        {
            std::cout << "Перший елемент: " << first_term  << " та різниця: " << common_difference;
            
        }
};