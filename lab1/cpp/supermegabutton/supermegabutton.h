#ifndef SUPERMEGABUTTON_H
#define SUPERMEGABUTTON_H

#include <QMainWindow>

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

private:
    Ui::SuperMegaButton *ui;
};
#endif // SUPERMEGABUTTON_H
