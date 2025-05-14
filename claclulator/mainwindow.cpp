#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <cmath>

//
void OperationCommand::execute() {
    *addTrigger = false;
    *subTrigger = false;
    *mulTrigger = false;
    *divTrigger = false;
    *percentTrigger = false;
    *powerTrigger = false;
    *logTrigger = false;

    if (displayText == "+") *addTrigger = true;
    else if (displayText == "-") *subTrigger = true;
    else if (displayText == "x") *mulTrigger = true;
    else if (displayText == "/") *divTrigger = true;
    else if (displayText == "%") *percentTrigger = true;
    else if (displayText == "x^y") *powerTrigger = true;
    else if (displayText == "log") *logTrigger = true;

}

void OperationCommand::unexecute() {
    *addTrigger = oldAddTrigger;
    *subTrigger = oldSubTrigger;
    *mulTrigger = oldMulTrigger;
    *divTrigger = oldDivTrigger;
    *percentTrigger = oldPercentTrigger;
    *powerTrigger = oldPowerTrigger;
    *logTrigger = oldLogTrigger;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->Output->setText(QString::number(calcValue));


    QPushButton *undoBtn = new QPushButton("<", this);
    QPushButton *redoBtn = new QPushButton(">", this);


    undoBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    redoBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);




    QGridLayout *topLayout = qobject_cast<QGridLayout*>(ui->centralwidget->layout()->itemAt(1)->layout());
    if (topLayout) {
        topLayout->addWidget(undoBtn, 0, 0);
        topLayout->addWidget(redoBtn, 0, 1);
    }

    connect(undoBtn, SIGNAL(released()), this, SLOT(Undo()));
    connect(redoBtn, SIGNAL(released()), this, SLOT(Redo()));


    QPushButton *sciBtn = new QPushButton("≡", this);
     sciBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


    if (topLayout) {
        topLayout->addWidget(sciBtn, 0, 2);
    }

    connect(sciBtn, &QPushButton::released, this, &MainWindow::toggleScientificPanel);


    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++)
    {
        QString butName;
        if (i == 0) {
            butName = "Zero";
        } else {
            butName = "Button" + QString::number(i);
        }
        numButtons[i] = MainWindow::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }


    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Multiple, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonsPressed()));
    connect(ui->Percent, SIGNAL(released()), this, SLOT(MathButtonsPressed()));


    connect(ui->Equal, SIGNAL(released()), this, SLOT(EqualButtonPressed()));
    connect(ui->Change_sign, SIGNAL(released()), this, SLOT(ChangeSignPressed()));
    connect(ui->Floating_point, SIGNAL(released()), this, SLOT(DecimalPressed()));
    connect(ui->Delete_all, SIGNAL(released()), this, SLOT(ClearAll()));
    connect(ui->Delete_num, SIGNAL(released()), this, SLOT(ClearCurrent()));


    setupScientificPanel();
}

MainWindow::~MainWindow()
{

    while (!undoStack.isEmpty())
    {
        delete undoStack.pop();
    }
    while (!redoStack.isEmpty())
    {
        delete redoStack.pop();
    }

    delete ui;
}

void MainWindow::setupScientificPanel()
{

    btnPi = new QPushButton("π", this);
    btnSqrt = new QPushButton("√", this);
    btnPower = new QPushButton("x^y", this);
    btnLog = new QPushButton("ln", this);


    btnPi->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btnSqrt->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btnPower->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    btnLog->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


    connect(btnPi, SIGNAL(released()), this, SLOT(PiPressed()));
    connect(btnSqrt, SIGNAL(released()), this, SLOT(SqrtPressed()));
    connect(btnPower, SIGNAL(released()), this, SLOT(PowerPressed()));
    connect(btnLog, SIGNAL(released()), this, SLOT(LogPressed()));


    btnPi->hide();
    btnSqrt->hide();
    btnPower->hide();
    btnLog->hide();


    QGridLayout *gridLayout = qobject_cast<QGridLayout*>(ui->centralwidget->layout()->itemAt(1)->layout());
    if (gridLayout) {
        gridLayout->addWidget(btnPi, 1, 4);
        gridLayout->addWidget(btnSqrt, 2, 4);
        gridLayout->addWidget(btnPower, 3, 4);
        gridLayout->addWidget(btnLog, 4, 4);
    }
}

void MainWindow::toggleScientificPanel()
{
    if (btnPi->isVisible()) {
        btnPi->hide();
        btnSqrt->hide();
        btnPower->hide();
        btnLog->hide();
    } else {
        btnPi->show();
        btnSqrt->show();
        btnPower->show();
        btnLog->show();
    }
}

void MainWindow::NumPressed()
{
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Output->text();

    if(displayVal.toDouble() == 0 || displayVal == "0") {
        ui->Output->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Output->setText(QString::number(dblNewVal, 'g', 16));
    }


    lastValue = displayVal.toDouble();
}

void MainWindow::MathButtonsPressed()
{

    Command *cmd = new OperationCommand(this, ui->Output->text(), calcValue,
                                        &addTrigger, &subTrigger, &mulTrigger,
                                        &divTrigger, &percentTrigger, &powerTrigger,
                                        &logTrigger);

    redoStack.clear();
    undoStack.push(cmd);

    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    percentTrigger = false;
    powerTrigger = false;
    logTrigger = false;

    QString displayVal = ui->Output->text();
    calcValue = displayVal.toDouble();

    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0) {
        divTrigger = true;
    } else if(QString::compare(butVal, "x", Qt::CaseInsensitive) == 0) {
        mulTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0) {
        addTrigger = true;
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0) {
        subTrigger = true;
    } else if(QString::compare(butVal, "%", Qt::CaseInsensitive) == 0) {
        percentTrigger = true;
    } else if(QString::compare(butVal, "x^y", Qt::CaseInsensitive) == 0) {
        powerTrigger = true;
    } else if(QString::compare(butVal, "log", Qt::CaseInsensitive) == 0 ||
               QString::compare(butVal, "ln", Qt::CaseInsensitive) == 0) {
        logTrigger = true;
    }

    ui->Output->setText("0");
}

void MainWindow::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Output->text();
    double dblDisplayVal = displayVal.toDouble();


    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    if(addTrigger || subTrigger || mulTrigger || divTrigger || percentTrigger || powerTrigger || logTrigger)
    {
        if(addTrigger) solution = calcValue + dblDisplayVal;
        else if(subTrigger) solution = calcValue - dblDisplayVal;
        else if(mulTrigger) solution = calcValue * dblDisplayVal;
        else if(divTrigger)
            {
                if(dblDisplayVal != 0) solution = calcValue / dblDisplayVal;
                else
                {
                    ui->Output->setText("Error");
                    return;
                }
        }
        else if(percentTrigger) solution = calcValue * (dblDisplayVal / 100.0);
        else if(powerTrigger) solution = pow(calcValue, dblDisplayVal);
        else if(logTrigger)
        {
            if(dblDisplayVal > 0) solution = log(dblDisplayVal) / log(calcValue);
            else
            {
                ui->Output->setText("Error");
                return;
            }
        }
    }
    else solution = dblDisplayVal;


    ui->Output->setText(QString::number(solution, 'g', 16));


    addTrigger = false;
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    percentTrigger = false;
    powerTrigger = false;
    logTrigger = false;

    calcValue = solution;
}

void MainWindow::ChangeSignPressed()
{
    QString displayVal = ui->Output->text();
    double dblDisplayVal = displayVal.toDouble();


    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    dblDisplayVal = -dblDisplayVal;

    ui->Output->setText(QString::number(dblDisplayVal, 'g', 16));
}

void MainWindow::DecimalPressed()
{
    QString displayVal = ui->Output->text();


    if(!displayVal.contains('.')) {
        displayVal.append('.');
        ui->Output->setText(displayVal);
    }
}

void MainWindow::ClearAll()
{

    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    calcValue = 0.0;
    ui->Output->setText(QString::number(calcValue));


    addTrigger = false;
    subTrigger = false;
    mulTrigger = false;
    divTrigger = false;
    percentTrigger = false;
    powerTrigger = false;
    logTrigger = false;
}

void MainWindow::ClearCurrent()
{

    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    ui->Output->setText("0");
}

void MainWindow::PiPressed()
{

    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    double pi = M_PI;
    ui->Output->setText(QString::number(pi, 'g', 16));
}

void MainWindow::SqrtPressed()
{
    QString displayVal = ui->Output->text();
    double dblDisplayVal = displayVal.toDouble();

    Command *cmd = new ValueCommand(&calcValue, calcValue);
    undoStack.push(cmd);
    redoStack.clear();

    if(dblDisplayVal >= 0) {
        double sqrtVal = sqrt(dblDisplayVal);
        ui->Output->setText(QString::number(sqrtVal, 'g', 16));
        calcValue = sqrtVal;
    } else {
        ui->Output->setText("Error");
    }
}

void MainWindow::PowerPressed()
{
    MathButtonsPressed();
    powerTrigger = true;
}

void MainWindow::LogPressed()
{
    MathButtonsPressed();
    logTrigger = true;
}

void MainWindow::Undo()
{
    if (!undoStack.isEmpty()) {
        Command *command = undoStack.pop();
        command->unexecute();
        redoStack.push(command);


        ui->Output->setText(QString::number(calcValue, 'g', 16));
    }
}

void MainWindow::Redo()
{
    if (!redoStack.isEmpty())
    {
        Command *command = redoStack.pop();
        command->execute();
        undoStack.push(command);


        ui->Output->setText(QString::number(calcValue, 'g', 16));
    }
}
