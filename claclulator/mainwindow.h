#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QGridLayout>
#include <QPushButton>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
    virtual void unexecute() = 0;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    double calcValue = 0.0;
    double lastValue = 0.0;
    bool divTrigger = false;
    bool mulTrigger = false;
    bool addTrigger = false;
    bool subTrigger = false;
    bool percentTrigger = false;
    bool powerTrigger = false;
    bool logTrigger = false;


    QPushButton *btnPi;
    QPushButton *btnSqrt;
    QPushButton *btnPower;
    QPushButton *btnLog;


    QStack<Command*> undoStack;
    QStack<Command*> redoStack;

    void undoAction();
    void redoAction();

    void setupScientificPanel();
    void toggleScientificPanel();

private slots:
    void NumPressed();
    void MathButtonsPressed();
    void EqualButtonPressed();
    void ChangeSignPressed();
    void DecimalPressed();
    void ClearAll();
    void ClearCurrent();


    void PiPressed();
    void SqrtPressed();
    void PowerPressed();
    void LogPressed();


    void Undo();
    void Redo();
};


class ValueCommand : public Command {
public:
    ValueCommand(double* targetValue, double newValue) :
        targetValue(targetValue), oldValue(*targetValue), newValue(newValue) {}

    void execute() override {
        *targetValue = newValue;
    }

    void unexecute() override {
        *targetValue = oldValue;
    }

private:
    double* targetValue;
    double oldValue;
    double newValue;
};


class OperationCommand : public Command
{
public:
    OperationCommand(MainWindow* window, QString displayText, double calcValue,
                     bool* addTrigger, bool* subTrigger, bool* mulTrigger,
                     bool* divTrigger, bool* percentTrigger, bool* powerTrigger,
                     bool* logTrigger)
        : window(window), displayText(displayText), calcValue(calcValue),
        addTrigger(addTrigger), subTrigger(subTrigger),
        mulTrigger(mulTrigger), divTrigger(divTrigger),
        percentTrigger(percentTrigger), powerTrigger(powerTrigger),
        logTrigger(logTrigger) {
        oldAddTrigger = *addTrigger;
        oldSubTrigger = *subTrigger;
        oldMulTrigger = *mulTrigger;
        oldDivTrigger = *divTrigger;
        oldPercentTrigger = *percentTrigger;
        oldPowerTrigger = *powerTrigger;
        oldLogTrigger = *logTrigger;
    }

    void execute() override;
    void unexecute() override;

private:
    MainWindow* window;
    QString displayText;
    double calcValue;
    bool* addTrigger;
    bool* subTrigger;
    bool* mulTrigger;
    bool* divTrigger;
    bool* percentTrigger;
    bool* powerTrigger;
    bool* logTrigger;
    bool oldAddTrigger;
    bool oldSubTrigger;
    bool oldMulTrigger;
    bool oldDivTrigger;
    bool oldPercentTrigger;
    bool oldPowerTrigger;
    bool oldLogTrigger;
};

#endif // MAINWINDOW_H
