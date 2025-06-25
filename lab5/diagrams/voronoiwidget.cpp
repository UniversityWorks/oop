#include "voronoiwidget.h"
#include "voronoi_calculator.h"
#include <QPainter>
#include <QThread>
#include <QThreadPool>
#include <QMutex>
#include <algorithm>
#include <cmath>

VoronoiWidget::VoronoiWidget(QWidget* parent)
    : QWidget(parent), m_gen(m_rd()) {
    setFixedSize(800, 600);
    m_image = QImage(800, 600, QImage::Format_RGB32);
    m_image.fill(Qt::white);
    m_metric = MetricType::EUCLIDEAN;
    m_useMultithread = true;
    m_threadCount = QThread::idealThreadCount();
    m_lastCalculationTime = 0;
}

void VoronoiWidget::addPoint(int x, int y) {

    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        m_points.emplace_back(x, y);
        calculateVoronoi();
    }
}

void VoronoiWidget::removePoint(int x, int y) {
    auto it = std::find_if(m_points.begin(), m_points.end(),
                           [x, y](const Point& p) {
                               return abs(p.x - x) < 10 && abs(p.y - y) < 10;
                           });

    if (it != m_points.end()) {
        m_points.erase(it);
        calculateVoronoi();
    }
}

void VoronoiWidget::generateRandomPoints(int count) {
    m_points.clear();
    std::uniform_int_distribution<> xDist(10, width() - 10);
    std::uniform_int_distribution<> yDist(10, height() - 10);

    for (int i = 0; i < count; ++i) {
        m_points.emplace_back(xDist(m_gen), yDist(m_gen));
    }

    calculateVoronoi();
}

void VoronoiWidget::clearPoints() {
    m_points.clear();
    m_image.fill(Qt::white);
    m_areas.clear();
    update();
    emit statisticsChanged();
}

void VoronoiWidget::setMetric(MetricType metric) {
    if (m_metric != metric) {
        m_metric = metric;
        calculateVoronoi();
    }
}

void VoronoiWidget::setMultithread(bool enabled) {
    if (m_useMultithread != enabled) {
        m_useMultithread = enabled;
        calculateVoronoi();
    }
}

void VoronoiWidget::setThreadCount(int count) {
    if (count > 0 && m_threadCount != count) {
        m_threadCount = count;
        if (m_useMultithread) {
            calculateVoronoi();
        }
    }
}

void VoronoiWidget::removeSmallestAreas(int percentage) {
    if (m_areas.empty() || percentage <= 0) return;


    std::vector<std::pair<int, int>> areaVector(m_areas.begin(), m_areas.end());
    std::sort(areaVector.begin(), areaVector.end(),
              [](const auto& a, const auto& b) { return a.second < b.second; });

    int toRemove = std::min(static_cast<int>((areaVector.size() * percentage) / 100),
                            static_cast<int>(areaVector.size()));


    std::vector<int> indicesToRemove;
    for (int i = 0; i < toRemove; ++i) {
        indicesToRemove.push_back(areaVector[i].first);
    }
    std::sort(indicesToRemove.rbegin(), indicesToRemove.rend());


    for (int index : indicesToRemove) {
        if (index >= 0 && index < static_cast<int>(m_points.size())) {
            m_points.erase(m_points.begin() + index);
        }
    }

    calculateVoronoi();
}

std::pair<QString, std::unordered_map<int, int>> VoronoiWidget::getStatistics() const {
    QString stats = QString("Точок: %1\n").arg(m_points.size());
    stats += QString("Метрика: %1\n").arg(
        m_metric == MetricType::EUCLIDEAN ? "Евклідова" :
            m_metric == MetricType::MANHATTAN ? "Манхеттенська" : "Чебишева");
    stats += QString("Багатопоточність: %1\n").arg(m_useMultithread ? "Так" : "Ні");
    stats += QString("Час обчислення: %1 мс\n").arg(m_lastCalculationTime);
    stats += QString("Потоків: %1\n").arg(m_threadCount);

    return {stats, m_areas};
}

void VoronoiWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.drawImage(0, 0, m_image);


    painter.setPen(QPen(Qt::black, 3));
    for (const auto& point : m_points) {
        painter.drawEllipse(point.x - 3, point.y - 3, 6, 6);
    }
}

void VoronoiWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        addPoint(event->x(), event->y());
    } else if (event->button() == Qt::RightButton) {
        removePoint(event->x(), event->y());
    }
}

void VoronoiWidget::calculateVoronoi() {
    if (m_points.empty()) {
        m_image.fill(Qt::white);
        m_areas.clear();
        update();
        emit statisticsChanged();
        return;
    }

    QElapsedTimer timer;
    timer.start();

    m_areas.clear();

    if (m_useMultithread) {
        calculateVoronoiMultithread();
    } else {
        calculateVoronoiSinglethread();
    }

    m_lastCalculationTime = timer.elapsed();
    update();
    emit statisticsChanged();
}

void VoronoiWidget::calculateVoronoiSinglethread() {
    for (int y = 0; y < m_image.height(); ++y) {
        for (int x = 0; x < m_image.width(); ++x) {
            int closestIndex = findClosestPoint(x, y);
            if (closestIndex != -1) {
                m_image.setPixelColor(x, y, m_points[closestIndex].color);
                m_areas[closestIndex]++;
            }
        }
    }
}

void VoronoiWidget::calculateVoronoiMultithread() {
    QMutex mutex;

    int tilesX = 4;
    int tilesY = 4;
    int tileWidth = m_image.width() / tilesX;
    int tileHeight = m_image.height() / tilesY;

    QThreadPool::globalInstance()->setMaxThreadCount(m_threadCount);

    for (int ty = 0; ty < tilesY; ++ty) {
        for (int tx = 0; tx < tilesX; ++tx) {
            int startX = tx * tileWidth;
            int endX = (tx == tilesX - 1) ? m_image.width() : (tx + 1) * tileWidth;
            int startY = ty * tileHeight;
            int endY = (ty == tilesY - 1) ? m_image.height() : (ty + 1) * tileHeight;

            VoronoiCalculator* calculator = new VoronoiCalculator(
                &m_image, m_points, startX, endX, startY, endY,
                m_metric, &mutex, &m_areas);

            QThreadPool::globalInstance()->start(calculator);
        }
    }

    QThreadPool::globalInstance()->waitForDone();
}

int VoronoiWidget::findClosestPoint(int x, int y) {
    if (m_points.empty()) return -1;

    int closestIndex = 0;
    double minDistance = calculateDistance(x, y, m_points[0].x, m_points[0].y);

    for (size_t i = 1; i < m_points.size(); ++i) {
        double distance = calculateDistance(x, y, m_points[i].x, m_points[i].y);
        if (distance < minDistance) {
            minDistance = distance;
            closestIndex = static_cast<int>(i);
        }
    }

    return closestIndex;
}

double VoronoiWidget::calculateDistance(int x1, int y1, int x2, int y2) {
    switch (m_metric) {
    case MetricType::EUCLIDEAN:
        return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    case MetricType::MANHATTAN:
        return abs(x1-x2) + abs(y1-y2);
    case MetricType::CHEBYSHEV:
        return std::max(abs(x1-x2), abs(y1-y2));
    }
    return 0;
}
