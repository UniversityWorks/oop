#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(nullptr));

    no_button = new QPushButton("Ні", this);
    no_button->setGeometry(400, 240, 111, 71);

    no_button->installEventFilter(this);

    connect(ui->yes_button, SIGNAL(clicked()), this, SLOT(on_yes_button_pressed()));
}

MainWindow::~MainWindow()
{
    delete no_button;
    delete ui;
}


bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == no_button && event->type() == QEvent::Enter) {
        move_button();
        return true;
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_yes_button_pressed()
{
    QMessageBox info;
    info.setText(QString("Правильно"));
    info.setStyleSheet("QLabel{min-width:300 px; min-height:120px; font-size: 14px;} QPushButton{ width:150px; font-size: 13px; }");
    info.exec();
}

void MainWindow::move_button()
{
    int x, y;
    do {
        x = rand() % 650;
        y = rand() % 450;
    } while((y > 50 && y < 380) && (x > 180 && x < 580));

    this->no_button->move(x, y);
}
