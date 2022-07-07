#include "calculator.h"
#include "./ui_calculator.h"
#include "controller.h"
#include "qstringliteral.h"
#include <string>
#include <iostream>


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    reset = false;
    model = new QStringListModel();
    ui->listView->setModel(model);
    connect(ui->button0, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button1, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button2, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button3, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button4, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button5, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button6, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button7, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button8, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->button9, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->buttonSum, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->buttonSubtract, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->buttonMultiply, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->buttonDivide, &QPushButton::released, this, &Calculator::clicked);
    connect(ui->buttonEquals, &QPushButton::released, this, &Calculator::equals);
    connect(ui->buttonC, &QPushButton::released, this, &Calculator::erase);
    connect(ui->buttonComma, &QPushButton::released, this, &Calculator::clicked);
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString currentExpression = ui->label->text();
    if (!reset) {
        if (!currentExpression.compare(QStringLiteral("0")) && button->text() != ','){
            currentExpression = button->text();
        }
        else {
            currentExpression.append(button->text());
        }
        ui->label->setText(currentExpression);
    }
    else {
        ui->label->setText(button->text());
        reset = false;
    }
}

void Calculator::erase()
{
    if (!reset) {
        QString currentText = ui->label->text();
        currentText.chop(1);
        ui->label->setText(currentText);
    }
    else {
        reset = false;
        ui->label->setText("0");
    }
}

void Calculator::equals()
{
    // Change
    Controller *c = new Controller();
    reset = true;

    const std::string result = c->compute(ui->label->text().toStdString());
    QString currentText = ui->label->text() + " = " + QString::fromStdString(result);

    model->setStringList(QStringList() << currentText << model->stringList());
    ui->label->setText(QString::fromStdString(result));
}



