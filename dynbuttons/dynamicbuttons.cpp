#include "dynamicbuttons.h"
#include "./ui_dynamicbuttons.h"

DynamicButtons::DynamicButtons(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynamicButtons)
{
    ui->setupUi(this);
}

DynamicButtons::~DynamicButtons()
{
    delete ui;
}

void DynamicButtons::on_pushButton_clicked()
{

}

