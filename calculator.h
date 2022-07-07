#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator() override;

private slots:
    void clicked();
    void equals();
    void erase();

private:
    bool reset;
    QStringListModel *model;
    Ui::Calculator *ui;

};
#endif // CALCULATOR_H
