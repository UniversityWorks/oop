#ifndef SUPERMEGABUTTON_H
#define SUPERMEGABUTTON_H

#include <QMainWindow>
#include <QStringList>

QT_BEGIN_NAMESPACE
namespace Ui {
class SuperMegaButton;
}
QT_END_NAMESPACE

class SuperMegaButton : public QMainWindow
{
    Q_OBJECT

public:
    SuperMegaButton(QWidget *parent = nullptr);
    ~SuperMegaButton();

private slots:
    void on_hello_world_button_clicked();
    void on_opacity_button_clicked();
    void on_bg_button_clicked();
    void on_super_button_clicked();

    void on_hello_world_checkbox_stateChanged(int state);
    void on_opacity_checkbox_stateChanged(int state);
    void on_bg_checkbox_stateChanged(int state);

private:
    Ui::SuperMegaButton *ui;
    QStringList checkboxOrder;
};

#endif // SUPERMEGABUTTON_H
