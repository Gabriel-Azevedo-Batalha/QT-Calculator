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
    connect(ui->button0, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button1, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button2, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button3, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button4, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button5, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button6, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button7, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button8, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->button9, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->buttonSum, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->buttonSubtract, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->buttonMultiply, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->buttonDivide, SIGNAL(released()), this, SLOT(clicked()));
    connect(ui->buttonEquals, SIGNAL(released()), this, SLOT(equals()));
    connect(ui->buttonC, SIGNAL(released()), this, SLOT(erase()));
    connect(ui->buttonComma, SIGNAL(released()), this, SLOT(clicked()));
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



