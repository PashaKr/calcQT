#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeCalculator();
    connectButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeCalculator()
{
    currentState = FirstDigit;
    firstNumber = 0;
    secondNumber = 0;
    memoryValue = 0;
    currentOperation = "";
    pendingOperation = "+";
    isFirstOperation = true;
    afterOperation = false;
    afterEqual = false;
    memoryEnabled = false;
    errorOccurred = false;

    ui->leRes->setText("0");
    ui->lbl_history->clear();
}

void MainWindow::connectButtons()
{
    QPushButton* digitButtons[10] = {
        ui->pb_0, ui->pb_1, ui->pb_2, ui->pb_3, ui->pb_4,
        ui->pb_5, ui->pb_6, ui->pb_7, ui->pb_8, ui->pb_9
    };

    for (int i = 0; i < 10; ++i) {
        connect(digitButtons[i], &QPushButton::clicked, this, &MainWindow::digitClicked);
    }
    connect(ui->pbpl, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pbmin, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pbpr, &QPushButton::clicked, this, &MainWindow::operatorClicked);
    connect(ui->pbdiv, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    connect(ui->pbequal, &QPushButton::clicked, this, &MainWindow::equalClicked);
    connect(ui->pb_C, &QPushButton::clicked, this, &MainWindow::clearAll);
    connect(ui->pb_CE, &QPushButton::clicked, this, &MainWindow::clearEntry);
    connect(ui->pbdot, &QPushButton::clicked, this, &MainWindow::decimalClicked);
    connect(ui->pbplmin, &QPushButton::clicked, this, &MainWindow::signChanged);

    connect(ui->pb_MC, &QPushButton::clicked, this, &MainWindow::memoryOperation);
    connect(ui->pb_MR, &QPushButton::clicked, this, &MainWindow::memoryOperation);
    connect(ui->pb_MS, &QPushButton::clicked, this, &MainWindow::memoryOperation);
    connect(ui->pb_Mpl, &QPushButton::clicked, this, &MainWindow::memoryOperation);
    connect(ui->pb_Mmin, &QPushButton::clicked, this, &MainWindow::memoryOperation);
}

void MainWindow::digitClicked()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString digit = button->text();

    if (currentState == FirstDigit) {
        if (afterEqual)
            clearAll();
        ui->leRes->clear();
        currentState = InputNumber;
    }

    ui->leRes->setText(ui->leRes->text() + digit);
}

void MainWindow::operatorClicked()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    if (pendingOperation == "/" && ui->leRes->text().toDouble() == 0) {
        showError("Division by zero");
        return;
    }

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString newOperator = button->text();

    if (currentState == InputNumber) {
        secondNumber = ui->leRes->text().toDouble();
        calculate(secondNumber, pendingOperation);
    }

    pendingOperation = newOperator;
    currentOperation = newOperator;
    ui->lbl_history->setText(QString::number(firstNumber) + " " + newOperator);
    afterOperation = true;
    afterEqual = false;
    currentState = FirstDigit;
}

void MainWindow::equalClicked()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    if (pendingOperation == "/" && ui->leRes->text().toDouble() == 0) {
        showError("Division by zero");
        return;
    }

    if (!afterEqual) {
        secondNumber = ui->leRes->text().toDouble();
    }

    if (currentState == InputNumber || afterOperation) {
        ui->lbl_history->setText(ui->lbl_history->text() + " " + ui->leRes->text() + " =");
        calculate(secondNumber, pendingOperation);
    }
    else {
        ui->lbl_history->setText(QString::number(firstNumber) + " " + pendingOperation + " " + QString::number(secondNumber) + " =");
        calculate(secondNumber, pendingOperation);
    }

    afterEqual = true;
    currentState = FirstDigit;
}

void MainWindow::decimalClicked()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    QString current = ui->leRes->text();
    if (currentState == FirstDigit) {
        ui->leRes->setText("0.");
        currentState = InputNumber;
    }
    else if (!current.contains('.')) {
        ui->leRes->setText(current + ".");
    }
}

void MainWindow::signChanged()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    QString current = ui->leRes->text();
    if (!current.isEmpty()) {
        double value = current.toDouble();
        ui->leRes->setText(QString::number(-value));
    }
}

void MainWindow::clearEntry()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    ui->leRes->setText("0");
    currentState = FirstDigit;
}

void MainWindow::clearAll()
{
    ui->leRes->setText("0");
    ui->lbl_history->clear();
    firstNumber = 0;
    secondNumber = 0;
    currentOperation = "";
    pendingOperation = "+";
    isFirstOperation = true;
    afterOperation = false;
    afterEqual = false;
    currentState = FirstDigit;
    errorOccurred = false;
}

void MainWindow::memoryOperation()
{
    if (errorOccurred) {
        showError("Division by zero");
        return;
    }

    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString operation = button->text();
    double currentValue = ui->leRes->text().toDouble();

    if (operation == "MC") {
        memoryValue = 0;
        memoryEnabled = false;
    }
    else if (operation == "MR" && memoryEnabled) {
        ui->leRes->setText(QString::number(memoryValue));
    }
    else if (operation == "MS") {
        memoryValue = currentValue;
        memoryEnabled = true;
    }
    else if (operation == "M+" && memoryEnabled) {
        memoryValue += currentValue;
    }
    else if (operation == "M-" && memoryEnabled) {
        memoryValue -= currentValue;
    }
}

void MainWindow::calculate(double operand, const QString &operation)
{
    if (isFirstOperation) {
        firstNumber = operand;
        isFirstOperation = false;
    }
    else {
        if (operation == "+")
            firstNumber += operand;
        else if (operation == "-")
            firstNumber -= operand;
        else if (operation == "*")
            firstNumber *= operand;
        else if (operation == "/") {
            if (operand == 0) {
                showError("Division by zero");
                return;
            }
            firstNumber /= operand;
        }
    }
    ui->leRes->setText(QString::number(firstNumber));
}

void MainWindow::showError(const QString &message)
{
    if (!errorOccurred) {
        errorOccurred = true;
        ui->leRes->setText("Error");
        QMessageBox::critical(this, "Error", message);
    }
}
