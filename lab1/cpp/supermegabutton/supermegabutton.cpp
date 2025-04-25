#include "supermegabutton.h"
#include "./ui_supermegabutton.h"
#include <QMessageBox>

SuperMegaButton::SuperMegaButton(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SuperMegaButton)
{
    ui->setupUi(this);
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

}


void SuperMegaButton::on_bg_button_clicked()
{
    QString currentStyle = this->styleSheet();
    (currentStyle.isEmpty()) ?  setStyleSheet("QMainWindow { background-color: rgb(143, 240, 164); }") :  setStyleSheet("");
}


void SuperMegaButton::on_super_button_clicked()
{
    QMessageBox superbtn;
    superbtn.setText("Я суперкнопка.\nІ мене цього не позбавиш!!!");
    superbtn.setStandardButtons(QMessageBox::Ok);
    superbtn.setStyleSheet("QLabel{min-width:300 px; min-height:120px; font-size: 14px;} QPushButton{ width:150px; font-size: 13px; }");
    superbtn.exec();



    if(ui->bg_checkbox->isChecked())on_bg_button_clicked();
    if(ui->opacity_checkbox->isChecked())on_opacity_button_clicked();
    if(ui->hello_world_checkbox->isChecked())on_hello_world_button_clicked();

}

