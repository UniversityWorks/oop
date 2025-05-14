#include "supermegabutton.h"
#include "./ui_supermegabutton.h"
#include <QMessageBox>

SuperMegaButton::SuperMegaButton(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SuperMegaButton)
{
    ui->setupUi(this);

    connect(ui->hello_world_checkbox, &QCheckBox::stateChanged, this, &SuperMegaButton::on_hello_world_checkbox_stateChanged);
    connect(ui->opacity_checkbox, &QCheckBox::stateChanged, this, &SuperMegaButton::on_opacity_checkbox_stateChanged);
    connect(ui->bg_checkbox, &QCheckBox::stateChanged, this, &SuperMegaButton::on_bg_checkbox_stateChanged);
}

SuperMegaButton::~SuperMegaButton()
{
    delete ui;
}

void SuperMegaButton::on_hello_world_button_clicked()
{
    QMessageBox msg;
    msg.setText("Hello world!!!");
    msg.setStandardButtons(QMessageBox::Ok);
    msg.setStyleSheet("QLabel{min-width:300 px; min-height:120px; font-size: 14px;} QPushButton{ width:150px; font-size: 13px; }");
    msg.exec();
}

void SuperMegaButton::on_opacity_button_clicked()
{
    QMessageBox msgExeption;
    msgExeption.setText("GNOME does not support changing opacity window.");
    msgExeption.setStandardButtons(QMessageBox::Ok);
    msgExeption.setStyleSheet("QLabel{min-width:350 px; min-height:120px; font-size: 14px;} QPushButton{ width:150px; font-size: 13px; }");
    msgExeption.exec();
}

void SuperMegaButton::on_bg_button_clicked()
{
    QString currentStyle = this->styleSheet();
    (currentStyle.isEmpty()) ?
        setStyleSheet("QMainWindow { background-color: rgb(143, 240, 164); }") :
        setStyleSheet("");
}

void SuperMegaButton::on_super_button_clicked()
{
    QMessageBox superbtn;
    superbtn.setText("Я суперкнопка.\nІ мене цього не позбавиш!!!");
    superbtn.setStandardButtons(QMessageBox::Ok);
    superbtn.setStyleSheet("QLabel{min-width:300 px; min-height:120px; font-size: 14px;} QPushButton{ width:150px; font-size: 13px; }");
    superbtn.exec();

    for (const QString &action : checkboxOrder)
    {
        if (action == "hello") on_hello_world_button_clicked();
        else if (action == "opacity") on_opacity_button_clicked();
        else if (action == "bg") on_bg_button_clicked();
    }
}

void SuperMegaButton::on_hello_world_checkbox_stateChanged(int state)
{
    if (state == Qt::Checked && !checkboxOrder.contains("hello")) checkboxOrder.append("hello");
    else if (state == Qt::Unchecked)  checkboxOrder.removeAll("hello");
}

void SuperMegaButton::on_opacity_checkbox_stateChanged(int state)
{
    if (state == Qt::Checked && !checkboxOrder.contains("opacity")) checkboxOrder.append("opacity");
    else if (state == Qt::Unchecked) checkboxOrder.removeAll("opacity");
}

void SuperMegaButton::on_bg_checkbox_stateChanged(int state)
{
    if (state == Qt::Checked && !checkboxOrder.contains("bg")) checkboxOrder.append("bg");
    else if (state == Qt::Unchecked) checkboxOrder.removeAll("bg");
}
