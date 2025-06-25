#include "voronoi_calculator.h"
#include <QMutexLocker>

VoronoiCalculator::VoronoiCalculator(QImage* image, const std::vector<Point>& points,
int startX, int endX, int startY, int endY, MetricType metric, QMutex* mutex, std::unordered_map<int, int>* areas)
    : m_image(image), m_points(points), m_startX(startX), m_endX(endX),
    m_startY(startY), m_endY(endY), m_metric(metric), m_mutex(mutex), m_areas(areas) {}

void VoronoiCalculator::run()
{
    std::unordered_map<int, int> localAreas;


    QImage localImage = m_image->copy();

    for (int y = m_startY; y < m_endY; ++y)
    {
        for (int x = m_startX; x < m_endX; ++x)
        {
            int closestIndex = findClosestPoint(x, y);
            if (closestIndex != -1)
            {
                localImage.setPixelColor(x, y, m_points[closestIndex].color);
                localAreas[closestIndex]++;
            }
        }
    }


    {
        QMutexLocker locker(m_mutex);
        for (int y = m_startY; y < m_endY; ++y)
        {
            for (int x = m_startX; x < m_endX; ++x)
            {
                m_image->setPixelColor(x, y, localImage.pixelColor(x, y));
            }
        }


        for (const auto& pair : localAreas)
        {
            (*m_areas)[pair.first] += pair.second;
        }
    }
}

int VoronoiCalculator::findClosestPoint(int x, int y)
{
    if (m_points.empty()) return -1;

    int closestIndex = 0;
    double minDistance = calculateDistance(x, y, m_points[0].x, m_points[0].y);

    for (size_t i = 1; i < m_points.size(); ++i) {

        if (shouldSkipPoint(x, y, m_points[i].x, m_points[i].y, minDistance))
        {
            continue;
        }

        double distance = calculateDistance(x, y, m_points[i].x, m_points[i].y);
        if (distance < minDistance)
        {
            minDistance = distance;
            closestIndex = static_cast<int>(i);
        }
    }

    return closestIndex;
}

bool VoronoiCalculator::shouldSkipPoint(int x, int y, int px, int py, double currentMin)
{

    if (m_metric == MetricType::EUCLIDEAN)
    {
        double manhattanDist = abs(x - px) + abs(y - py);
        return manhattanDist > currentMin;
    }
    return false;
}

double VoronoiCalculator::calculateDistance(int x1, int y1, int x2, int y2)
{
    switch (m_metric)
    {
        case MetricType::EUCLIDEAN:
            return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
        case MetricType::MANHATTAN:
            return abs(x1-x2) + abs(y1-y2);
        case MetricType::CHEBYSHEV:
            return std::max(abs(x1-x2), abs(y1-y2));
    }
    return 0;
}
