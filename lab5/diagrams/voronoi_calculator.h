#ifndef VORONOI_CALCULATOR_H
#define VORONOI_CALCULATOR_H

#include <QRunnable>
#include <QImage>
#include <QMutex>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include "point.h"
#include "metrictypes.h"

class VoronoiCalculator : public QRunnable
{
public:
    VoronoiCalculator(QImage* image, const std::vector<Point>& points,int startX, int endX,
    int startY, int endY, MetricType metric, QMutex* mutex, std::unordered_map<int, int>* areas);

    void run() override;

private:
    int findClosestPoint(int x, int y);
    bool shouldSkipPoint(int x, int y, int px, int py, double currentMin);
    double calculateDistance(int x1, int y1, int x2, int y2);

    QImage* m_image;
    const std::vector<Point>& m_points;
    int m_startX, m_endX, m_startY, m_endY;
    MetricType m_metric;
    QMutex* m_mutex;
    std::unordered_map<int, int>* m_areas;
};

#endif // VORONOI_CALCULATOR_H
