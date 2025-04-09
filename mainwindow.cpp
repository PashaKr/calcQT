#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    state = FirstDigit;
    first_number = 0;
    second_number = 0;
    mem = 0;

    is_first_oper = true;
    after_operation = false;
    after_equal = false;
    mem_ok = false;
    prev_operation = "+";

    connectButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectButtons()
{
    QPushButton* digits[10] = {
        ui->pb_0, ui->pb_1, ui->pb_2, ui->pb_3, ui->pb_4,
        ui->pb_5, ui->pb_6, ui->pb_7, ui->pb_8, ui->pb_9
    };

    for (int i = 0; i < 10; ++i)
        connect(digits[i], SIGNAL(clicked()), this, SLOT(on_digit_pushed()));

    connect(ui->pbpl, SIGNAL(clicked()), this, SLOT(on_operator_pushed()));
    connect(ui->pbmin, SIGNAL(clicked()), this, SLOT(on_operator_pushed()));
    connect(ui->pbpr, SIGNAL(clicked()), this, SLOT(on_operator_pushed()));
    connect(ui->pbdiv, SIGNAL(clicked()), this, SLOT(on_operator_pushed()));

    connect(ui->pbequal, SIGNAL(clicked()), this, SLOT(on_equal_pushed()));
    connect(ui->pb_C, SIGNAL(clicked()), this, SLOT(lclear()));
    connect(ui->pb_CE, SIGNAL(clicked()), this, SLOT(on_CE_pushed()));
    connect(ui->pbdot, SIGNAL(clicked()), this, SLOT(on_dot_pushed()));
    connect(ui->pbplmin, SIGNAL(clicked()), this, SLOT(on_inverse_pushed()));

    connect(ui->pb_MC, SIGNAL(clicked()), this, SLOT(on_mem_pushed()));
    connect(ui->pb_MR, SIGNAL(clicked()), this, SLOT(on_mem_pushed()));
    connect(ui->pb_MS, SIGNAL(clicked()), this, SLOT(on_mem_pushed()));
    connect(ui->pb_Mpl, SIGNAL(clicked()), this, SLOT(on_mem_pushed()));
    connect(ui->pb_Mmin, SIGNAL(clicked()), this, SLOT(on_mem_pushed()));
}

void MainWindow::on_digit_pushed()
{
    QPushButton* btn = (QPushButton*)sender();
    QString digit = btn->text();

    if (state == FirstDigit) {
        if (after_equal)
            lclear();
        ui->leRes->setText("");
        if (digit != "0")
            state = InputNumber;
    }

    ui->leRes->setText(ui->leRes->text() + digit);
}

void MainWindow::on_operator_pushed()
{
    QPushButton* btn = (QPushButton*)sender();
    QString op = btn->text();

    second_number = ui->leRes->text().toDouble();
    equal_operation = op;

    if (state == InputNumber) {
        calculate(second_number, prev_operation);
        if (prev_operation == "/" && second_number == 0) {
            first_number = 0;
            is_first_oper = true;
            showMessage("Деление на ноль");
        }
    }

    ui->lbl_history->setText(QString::number(first_number) + " " + op);
    prev_operation = op;
    after_operation = true;
    after_equal = false;
    state = FirstDigit;
}

void MainWindow::on_equal_pushed()
{
    if (!after_equal) {
        second_number = ui->leRes->text().toDouble();
        equal_operation = prev_operation;
    }

    if (after_operation) {
        ui->lbl_history->setText(ui->lbl_history->text() + " " + ui->leRes->text() + " =");
        calculate(second_number, equal_operation);
        after_operation = false;
    } else {
        ui->lbl_history->setText(QString::number(first_number) + " " + equal_operation + " " + QString::number(second_number) + " =");
        calculate(second_number, equal_operation);
    }

    after_equal = true;
    state = FirstDigit;
}

void MainWindow::on_dot_pushed()
{
    QString val = ui->leRes->text();
    if (state == FirstDigit)
        ui->leRes->setText("0.");
    else if (!val.contains("."))
        ui->leRes->setText(val + ".");

    state = InputNumber;
}

void MainWindow::on_inverse_pushed()
{
    QString val = ui->leRes->text();
    if (val.isEmpty())
        return;

    double d = val.toDouble();
    ui->leRes->setText(QString::number(-d));
    state = InputNumber;
}

void MainWindow::on_CE_pushed()
{
    ui->leRes->setText("0");
    state = FirstDigit;
}

void MainWindow::lclear()
{
    ui->leRes->setText("0");
    ui->lbl_history->setText("");

    state = FirstDigit;
    first_number = 0;
    second_number = 0;

    is_first_oper = true;
    after_operation = false;
    after_equal = false;

    prev_operation = "+";
}

void MainWindow::on_mem_pushed()
{
    QPushButton* btn = (QPushButton*)sender();
    QString cmd = btn->text();

    if (cmd == "M+") {
        mem += ui->leRes->text().toDouble();
        mem_ok = true;
    } else if (cmd == "M-") {
        mem -= ui->leRes->text().toDouble();
        mem_ok = true;
    } else if (cmd == "MS") {
        mem = ui->leRes->text().toDouble();
        mem_ok = true;
    } else if (cmd == "MC") {
        mem = 0;
        mem_ok = false;
        return;
    } else if (cmd == "MR") {
        if (mem_ok)
            ui->leRes->setText(QString::number(mem));
        return;
    }
}

void MainWindow::calculate(double second_number, const QString &operation)
{
    after_operation = false;

    if (is_first_oper) {
        first_number += second_number;
        is_first_oper = false;
    } else {
        if (operation == "+")
            first_number += second_number;
        else if (operation == "-")
            first_number -= second_number;
        else if (operation == "*")
            first_number *= second_number;
        else if (operation == "/") {
            if (second_number == 0) {
                lclear();
                showMessage("Деление на ноль");
                return;
            }
            first_number /= second_number;
        }
    }

    ui->leRes->setText(QString::number(first_number));
}

void MainWindow::showMessage(const QString &msg)
{
    QMessageBox::critical(this, "Ошибка", msg);
}
