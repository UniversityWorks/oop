#ifndef VORONOIWIDGET_H
#define VORONOIWIDGET_H

#include <QWidget>
#include <QImage>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QElapsedTimer>
#include <vector>
#include <unordered_map>
#include <random>
#include "point.h"
#include "metrictypes.h"

class VoronoiWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VoronoiWidget(QWidget* parent = nullptr);

    void addPoint(int x, int y);
    void removePoint(int x, int y);
    void generateRandomPoints(int count);
    void clearPoints();
    void setMetric(MetricType metric);
    void setMultithread(bool enabled);
    void setThreadCount(int count);
    void removeSmallestAreas(int percentage);

    std::pair<QString, std::unordered_map<int, int>> getStatistics() const;

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void statisticsChanged();

private:
    void calculateVoronoi();
    void calculateVoronoiSinglethread();
    void calculateVoronoiMultithread();
    int findClosestPoint(int x, int y);
    double calculateDistance(int x1, int y1, int x2, int y2);

    std::vector<Point> m_points;
    QImage m_image;
    MetricType m_metric;
    bool m_useMultithread;
    int m_threadCount;
    qint64 m_lastCalculationTime;
    std::unordered_map<int, int> m_areas;

    // Random generator
    std::random_device m_rd;
    std::mt19937 m_gen;
};

#endif // VORONOIWIDGET_H
