#include <iostream>
#include <cmath>

class TDisk
{
    protected:
        double R;
        double cX, cY;

    public:
        TDisk() : R(1), cX(0), cY(0){}

        TDisk(double r, double x, double y) : 
        R(r), cX(x), cY(y){}

        TDisk(const TDisk& other) : 
        R(other.R), cX(other.cX), cY(other.cY){}

        double area() const
        {
            return M_PI *R*R;
        }

        bool contains(double x, double y) const
        {
            double dist = sqrt(pow(x- cX, 2) + pow(y - cY, 2));
            return dist <= R;
        }

        TDisk operator*(double scalar) const {
        return TDisk(R * scalar, cX, cY);
    }

    friend TDisk operator*(double scalar, const TDisk& disk) {
        return TDisk(disk.R * scalar, disk.cX, disk.cY);
    }

    void out() const {
        std::cout << "Радіус: " << R << ", Центр: (" << cX << ", " << cY << ")" << std::endl;
    }
};

class TBall : public TDisk
{
    private:
        double cZ;

    public:
    TBall(): TDisk(), cZ(0){}

    TBall(double r, double x, double y, double z) : TDisk(r,x,y), cZ(z){}

    double volume() const
    {
        return (4.0 / 3.0) * M_PI * pow(R,3);
    }

    void out()
    {
        std::cout << "Радіус: " << R << ", центр: (" << cX << ';' << cY << ';' << cZ << ")." << std::endl;
    }
};