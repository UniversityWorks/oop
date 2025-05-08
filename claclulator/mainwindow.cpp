#include "mainwindow.h"
#include "./ui_mainwindow.h"

double calcValue = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //start
    ui->Output->setText(QString::number(calcValue));
    QPushButton *numButtons[10];

    for(int i =0; i < 10; i++)
    {
        QString butName = "Button"+ QString::number(i);
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Multiple, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Equal, SIGNAL(released()), this, SLOT(Equa()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Output->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0))
    {
        ui->Output->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Output->setText(QString::number(dblNewVal, 'g', 16));
    }
}
void MainWindow::MathButtonsPressed()
{
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;

    QString displayVal = ui->Output->text();
    calcValue = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){ divTrigger = true;}
    else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0) {mulTrigger = true;}
    else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {addTrigger = true;}
    else {subTrigger = true;}
    ui->Output->setText("");
}

void MainWindow::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Output->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger)
    {
        if(addTrigger){solution = calcValue+dblDisplayVal;}
        else if(subTrigger){solution = calcValue - dblDisplayVal;}
        else if(mulTrigger) {solution = calcValue * dblDisplayVal;}
        else {solution = calcValue / dblDisplayVal;}

    }

    ui->Output->setText(QString::number(solution));
}

// void MainWindow::ChangeNumberSign()
// {
//     QString displayVal = ui->Output->text();
//     QRegExp reg("[-]?[0-9.]*");
//     if(reg.exactMatch(displayVal))
//     {
//         double dblDisplayVal = displayVal.toDouble();
//         double dblDisplayValSign = -1 * dblDisplayVal;
//         ui->Output->setText(QString::number(dblDisplayValSign));
//     }
// }
