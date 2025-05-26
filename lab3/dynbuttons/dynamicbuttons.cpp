#include "dynamicbuttons.h"
#include "./ui_dynamicbuttons.h"
#include <QIntValidator>
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QLabel>

int get_value_from = 0;
int get_value_to = 0;
int get_value_move = 0;
int get_value_mul = 0;

std::vector<QPushButton* > generated_buttons;


DynamicButtons::DynamicButtons(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DynamicButtons)
{
    ui->setupUi(this);


    connect(ui->more_button, SIGNAL(pressed()), this, SLOT(on_more_button_pressed()));
    connect(ui->remove_button, SIGNAL(pressed()), this, SLOT(on_remove_button_pressed()));

    ui->from->setValidator(new QIntValidator(-32000, 32000, this));
    ui->to->setValidator(new QIntValidator(-32000, 32000, this));
    ui->move->setValidator(new QIntValidator(-32000, 32000, this));
    ui->mul->setValidator(new QIntValidator(-32000, 32000, this));

    connect(ui->from, SIGNAL(textChanged(QString)), this, SLOT(on_from_textChanged(QString)));
    connect(ui->to, SIGNAL(textChanged(QString)), this, SLOT(on_to_textChanged(QString)));
    connect(ui->move, SIGNAL(textChanged(QString)), this, SLOT(on_move_textChanged(QString)));
    connect(ui->mul, SIGNAL(textChanged(QString)), this, SLOT(on_mul_textChanged(QString)));
}


DynamicButtons::~DynamicButtons()
{

    clearButtons();
    delete ui;
}

//clear:

void DynamicButtons::clearButtons()
{
    QWidget *container = ui->scrollArea->widget();
    QLayout *layout = container->layout();
    if(get_value_mul == 0)
    {
        if (layout)
        {
            QLayoutItem *item;
            while ((item = layout->takeAt(0)) != nullptr)
            {
                delete item->widget();
                delete item;
            }
            delete layout;
        }
        generated_buttons.clear();
    }
    else
    {
        auto it = generated_buttons.begin();
        while (it != generated_buttons.end())
        {
            QPushButton *button = *it;
            bool ok;
            int value = button->text().toInt(&ok);
            if (ok && value % get_value_mul == 0)
            {
                layout->removeWidget(button);
                delete button;
                it = generated_buttons.erase(it);
            }
            else ++it;

        }
    }

}

void DynamicButtons::on_remove_button_pressed()
{
    clearButtons();
}

//Buttons
void DynamicButtons::on_more_button_pressed()
{
    if (get_value_move == 0) return;

    if ((get_value_move > 0 && get_value_from >= get_value_to) ||
        (get_value_move < 0 && get_value_from <= get_value_to))
        return;

    QWidget *container = ui->scrollArea->widget();


    QVBoxLayout *layout = qobject_cast<QVBoxLayout*>(container->layout());

    if (!layout)
    {
        layout = new QVBoxLayout(container);
        container->setLayout(layout);
    }

    for (int i = get_value_from; (get_value_move > 0) ? (i < get_value_to) : (i > get_value_to);  i += get_value_move)
    {
        QPushButton *button = new QPushButton(QString::number(i), container);
        layout->addWidget(button);
        generated_buttons.push_back(button);


        connect(button, &QPushButton::clicked, this, [=]() {showNumberInfo(i);});
    }
}
//QMessageBox:
void DynamicButtons::showNumberInfo(int number)
{
    QString text;
    bool already_clicked = false;
    if(!already_clicked)
    {
        already_clicked = true;
        if (number <= 1) text = QString::number(number) + " не є простим числом.";
        else
        {
            bool isPrime = true;
            for (int i = 2; i <= sqrt(number); ++i)
            {
                if (number % i == 0)
                {
                    text = QString("%1 є складеним числом.\nДілиться на: %2").arg(number).arg(i);
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) text = QString::number(number) + " є простим числом.";

        }
    }
    else
    {
        text = QString("Ви вже натискали на кнопку.");
    }

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("btn");

    QLabel* label = new QLabel(text);
    label->setWordWrap(true);
    label->setMinimumSize(250, 80);

    msgBox.layout()->addWidget(label);
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
}




//Line edits
void DynamicButtons::on_from_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        get_value_from = 0;
        return;
    }
    bool ok;

    int value= arg1.toInt(&ok);

    if(ok) get_value_from =  value;

}

void DynamicButtons::on_to_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        get_value_to = 0;
        return;
    }
    bool ok;

    int value= arg1.toInt(&ok);

    if(ok) get_value_to =  value;

}

void DynamicButtons::on_move_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        get_value_move = 0;
        return;
    }

    bool ok;

    int value= arg1.toInt(&ok);

    if(ok) get_value_move =  value;
}

void DynamicButtons::on_mul_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        get_value_mul = 0;
        return;
    }
    bool ok;

    int value= arg1.toInt(&ok);

    if(ok) get_value_mul =  value;

}
