#ifndef DYNAMICBUTTONS_H
#define DYNAMICBUTTONS_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class DynamicButtons;
}
QT_END_NAMESPACE

class DynamicButtons : public QMainWindow
{
    Q_OBJECT

public:
    DynamicButtons(QWidget *parent = nullptr);
    ~DynamicButtons();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DynamicButtons *ui;
};
#endif // DYNAMICBUTTONS_H
