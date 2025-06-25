#include "mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    connectSignals();
    updateStatistics();
}

void MainWindow::onGenerateRandom()
{
    m_voronoiWidget->generateRandomPoints(m_pointCountSpinBox->value());
}

void MainWindow::onClearPoints()
{
    m_voronoiWidget->clearPoints();
}

void MainWindow::onMetricChanged()
{
    MetricType metric = static_cast<MetricType>(m_metricComboBox->currentIndex());
    m_voronoiWidget->setMetric(metric);
}

void MainWindow::onMultithreadChanged()
{
    bool enabled = m_multithreadCheckBox->isChecked();
    m_voronoiWidget->setMultithread(enabled);
    m_threadCountSpinBox->setEnabled(enabled);
}

void MainWindow::onThreadCountChanged()
{
    m_voronoiWidget->setThreadCount(m_threadCountSpinBox->value());
}

void MainWindow::onRemoveSmallest()
{
    m_voronoiWidget->removeSmallestAreas(m_percentageSpinBox->value());
}

void MainWindow::updateStatistics()
{
    auto stats = m_voronoiWidget->getStatistics();
    m_statisticsText->setText(stats.first);

    QString areasText = "Площі локусів:\n";
    for (const auto& pair : stats.second)
    {
        areasText += QString("Точка %1: %2 пікселів\n").arg(pair.first).arg(pair.second);
    }
    m_areasText->setText(areasText);
}

void MainWindow::setupUI() {
    auto* centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    auto* mainLayout = new QHBoxLayout(centralWidget);

    m_voronoiWidget = new VoronoiWidget;
    mainLayout->addWidget(m_voronoiWidget);


    auto* controlPanel = new QWidget;
    controlPanel->setFixedWidth(300);
    auto* controlLayout = new QVBoxLayout(controlPanel);

    auto* randomGroup = new QWidget;
    auto* randomLayout = new QHBoxLayout(randomGroup);
    randomLayout->addWidget(new QLabel("Кількість точок:"));
    m_pointCountSpinBox = new QSpinBox;
    m_pointCountSpinBox->setRange(1, 1000);
    m_pointCountSpinBox->setValue(50);
    randomLayout->addWidget(m_pointCountSpinBox);

    auto* generateButton = new QPushButton("Згенерувати");
    randomLayout->addWidget(generateButton);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onGenerateRandom);

    controlLayout->addWidget(randomGroup);

    auto* clearButton = new QPushButton("Очистити");
    connect(clearButton, &QPushButton::clicked, this, &MainWindow::onClearPoints);
    controlLayout->addWidget(clearButton);


    controlLayout->addWidget(new QLabel("Метрика:"));
    m_metricComboBox = new QComboBox;
    m_metricComboBox->addItems({"Евклідова", "Манхеттенська", "Чебишева"});
    connect(m_metricComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onMetricChanged);
    controlLayout->addWidget(m_metricComboBox);

    m_multithreadCheckBox = new QCheckBox("Багатопоточність");
    m_multithreadCheckBox->setChecked(true);
    connect(m_multithreadCheckBox, &QCheckBox::toggled, this, &MainWindow::onMultithreadChanged);
    controlLayout->addWidget(m_multithreadCheckBox);


    auto* threadGroup = new QWidget;
    auto* threadLayout = new QHBoxLayout(threadGroup);
    threadLayout->addWidget(new QLabel("Потоків:"));
    m_threadCountSpinBox = new QSpinBox;
    m_threadCountSpinBox->setRange(1, 32);
    m_threadCountSpinBox->setValue(QThread::idealThreadCount());
    connect(m_threadCountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &MainWindow::onThreadCountChanged);
    threadLayout->addWidget(m_threadCountSpinBox);
    controlLayout->addWidget(threadGroup);


    auto* removeGroup = new QWidget;
    auto* removeLayout = new QHBoxLayout(removeGroup);
    removeLayout->addWidget(new QLabel("Видалити %:"));
    m_percentageSpinBox = new QSpinBox;
    m_percentageSpinBox->setRange(1, 50);
    m_percentageSpinBox->setValue(10);
    removeLayout->addWidget(m_percentageSpinBox);

    auto* removeButton = new QPushButton("Видалити");
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveSmallest);
    removeLayout->addWidget(removeButton);

    controlLayout->addWidget(removeGroup);

    controlLayout->addWidget(new QLabel("Статистика:"));
    m_statisticsText = new QTextEdit;
    m_statisticsText->setMaximumHeight(150);
    m_statisticsText->setReadOnly(true);
    controlLayout->addWidget(m_statisticsText);

    controlLayout->addWidget(new QLabel("Площі локусів:"));
    m_areasText = new QTextEdit;
    m_areasText->setReadOnly(true);
    controlLayout->addWidget(m_areasText);

    controlLayout->addStretch();

    mainLayout->addWidget(controlPanel);

    setWindowTitle("Diagrams");
    resize(1200, 700);
}

void MainWindow::connectSignals()
{
    connect(m_voronoiWidget, &VoronoiWidget::statisticsChanged,
            this, &MainWindow::updateStatistics);
}
