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


    void on_more_button_pressed();

    void on_remove_button_pressed();



    void on_from_textChanged(const QString &arg1);

    void on_to_textChanged(const QString &arg1);

    void on_move_textChanged(const QString &arg1);

    void on_mul_textChanged(const QString &arg1);

private:
    void showNumberInfo(int number);
    Ui::DynamicButtons *ui;
    void clearButtons();
};
#endif // DYNAMICBUTTONS_H
