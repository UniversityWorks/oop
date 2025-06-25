#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QPushButton>
#include "voronoiwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow() = default;

private slots:
    void onGenerateRandom();
    void onClearPoints();
    void onMetricChanged();
    void onMultithreadChanged();
    void onRemoveSmallest();
    void onThreadCountChanged();
    void updateStatistics();

private:
    void setupUI();
    void connectSignals();

    VoronoiWidget* m_voronoiWidget;
    QSpinBox* m_pointCountSpinBox;
    QSpinBox* m_percentageSpinBox;
    QSpinBox* m_threadCountSpinBox;
    QComboBox* m_metricComboBox;
    QCheckBox* m_multithreadCheckBox;
    QTextEdit* m_statisticsText;
    QTextEdit* m_areasText;
};

#endif // MAINWINDOW_H
