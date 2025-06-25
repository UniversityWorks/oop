#ifndef POINT_H
#define POINT_H

#include <QColor>
#include <random>

struct Point {
    int x, y;
    QColor color;

    Point(int x = 0, int y = 0) : x(x), y(y)
    {
        static thread_local std::random_device rd;
        static thread_local std::mt19937 gen(rd());
        static thread_local std::uniform_int_distribution<> colorDist(0, 255);

        color = QColor(colorDist(gen), colorDist(gen), colorDist(gen));
    }
};

#endif // POINT_H
