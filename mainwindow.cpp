#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include <QVector>
#include <QStack>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->leRes->setText("0");

    QList<QPushButton *> numButtons = {
        ui->pb_0, ui->pb_1, ui->pb_2, ui->pb_3, ui->pb_4,
        ui->pb_5, ui->pb_6, ui->pb_7, ui->pb_8, ui->pb_9
    };
    for (QPushButton *btn : numButtons)
        connect(btn, &QPushButton::clicked, this, &MainWindow::clicknum);

    connect(ui->pbdot, &QPushButton::clicked, this, &MainWindow::on_pbdot_clicked);

    QList<QPushButton*> opButtons = {
        ui->pbpl, ui->pbmin, ui->pbpr, ui->pbdiv
    };
    for (QPushButton *btn : opButtons)
        connect(btn, &QPushButton::clicked, this, &MainWindow::operatorClicked);

    connect(ui->pbequal, &QPushButton::clicked, [this]() { calc(); });
    connect(ui->pb_C, &QPushButton::clicked, this, &MainWindow::C);
    connect(ui->pb_CE, &QPushButton::clicked, this, &MainWindow::CE);
    connect(ui->pbplmin, &QPushButton::clicked, this, &MainWindow::changer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clicknum()
{
    if (errorState) return;

    QString text = dynamic_cast<QPushButton*>(sender())->text();
    QString current = ui->leRes->text();

    if (wasJustEvaluated) {
        // Пользователь начал новый ввод после "=" → начать с чистого числа
        ui->leRes->setText(text);
        wasJustEvaluated = false;
        newInputAfterEval = true;
        ui->lbl_history->clear();
    }
    else if (current == "0" || current == "Ошибка вычисления") {
        ui->leRes->setText(text);
    }
    else {
        ui->leRes->setText(current + text);
    }
}

void MainWindow::on_pbdot_clicked()
{
    if (errorState) return;

    QString current = ui->leRes->text();
    if (wasJustEvaluated || current == "Ошибка вычисления") {
        ui->leRes->setText("0.");
        wasJustEvaluated = false;
        newInputAfterEval = true;
        return;
    }

    QStringList parts = current.split(QRegularExpression("[+\\-*/]"), Qt::SkipEmptyParts);
    QString lastPart = parts.isEmpty() ? "" : parts.last();
    if (!lastPart.contains(".")) {
        ui->leRes->setText(current + ".");
    }
}

void MainWindow::operatorClicked()
{
    if (errorState) return;

    QString op = dynamic_cast<QPushButton*>(sender())->text();
    QString current = ui->leRes->text();

    if (wasJustEvaluated && newInputAfterEval) {
        // Ввели новое число после "=" → начинаем новое выражение
        ui->lbl_history->setText(current + " " + op + " ");
        ui->leRes->clear();
        lastResult = current.toDouble();
    }
    else if (wasJustEvaluated && !newInputAfterEval) {
        // Нажали оператор после "=" без ввода нового числа → продолжаем выражение
        ui->lbl_history->setText(current + " " + op + " ");
        ui->leRes->clear();
        lastResult = current.toDouble();
    }
    else if (!ui->lbl_history->text().isEmpty() && !current.isEmpty()) {
        // Промежуточное вычисление
        QString fullExpr = ui->lbl_history->text() + current;
        bool ok;
        double result = evaluateExpression(fullExpr, ok);

        if (!ok) {
            ui->leRes->setText("Ошибка вычисления");
            ui->leRes->setStyleSheet("background-color: rgb(255, 200, 200);");
            QMessageBox::critical(this, "Ошибка", "Невозможно вычислить выражение (возможно, деление на 0)");
            errorState = true;
            setButtonsEnabled(false);
            return;
        }

        ui->lbl_history->setText(QString::number(result) + " " + op + " ");
        ui->leRes->clear();
        lastResult = result;
    }
    else if (!current.isEmpty()) {
        ui->lbl_history->setText(current + " " + op + " ");
        ui->leRes->clear();
        lastResult = current.toDouble();
    }

    lastOperator = op;
    hasLastOperation = true;
    wasJustEvaluated = false;
    newInputAfterEval = false;
}


void MainWindow::C()
{
    ui->leRes->setText("0");
    ui->lbl_history->setText("");
    ui->leRes->setStyleSheet("");
    errorState = false;
    setButtonsEnabled(true);

    lastResult = 0;
    lastOperand = 0;
    lastOperator.clear();
    hasLastOperation = false;
    wasJustEvaluated = false;
    newInputAfterEval = false;
}


void MainWindow::CE()
{
    if (errorState) return;

    ui->leRes->setText("0");
    wasJustEvaluated = false;
    newInputAfterEval = false;
}


void MainWindow::changer()
{
    if (errorState) return;

    QString current = ui->leRes->text();
    if (!current.isEmpty() && current != "0" && current != "Ошибка вычисления") {
        double val = current.toDouble();
        ui->leRes->setText(QString::number(-val));
    }

    wasJustEvaluated = false;
    newInputAfterEval = true;
}


bool MainWindow::calc()
{
    if (errorState) return false;

    QString current = ui->leRes->text();
    QString history = ui->lbl_history->text();
    bool ok;

    if (!history.isEmpty() && !current.isEmpty() && !wasJustEvaluated) {
        // Пример: 9 + 4 → =
        QString expr = history + current;
        double result = evaluateExpression(expr, ok);

        if (!ok) {
            ui->leRes->setText("Ошибка вычисления");
            ui->leRes->setStyleSheet("background-color: rgb(255, 200, 200);");
            QMessageBox::critical(this, "Ошибка", "Невозможно вычислить выражение (возможно, деление на 0)");
            errorState = true;
            setButtonsEnabled(false);
            return false;
        }

        lastResult = result;
        lastOperand = current.toDouble();
        ui->leRes->setText(QString::number(result));
        ui->lbl_history->setText(expr + " =");
        hasLastOperation = true;
    }
    else if (hasLastOperation) {
        // Повторное нажатие "="
        QString expr = QString::number(lastResult) + " " + lastOperator + " " + QString::number(lastOperand);
        double result = evaluateExpression(expr, ok);

        if (!ok) {
            ui->leRes->setText("Ошибка вычисления");
            ui->leRes->setStyleSheet("background-color: rgb(255, 200, 200);");
            QMessageBox::critical(this, "Ошибка", "Невозможно вычислить выражение (возможно, деление на 0)");
            errorState = true;
            setButtonsEnabled(false);
            return false;
        }

        lastResult = result;
        ui->leRes->setText(QString::number(result));
        ui->lbl_history->setText(expr + " =");
    }

    wasJustEvaluated = true;
    return true;
}



void MainWindow::setButtonsEnabled(bool enabled)
{
    QList<QPushButton*> buttons = {
        ui->pb_0, ui->pb_1, ui->pb_2, ui->pb_3, ui->pb_4,
        ui->pb_5, ui->pb_6, ui->pb_7, ui->pb_8, ui->pb_9,
        ui->pb_MC, ui->pb_MR, ui->pb_MS, ui->pb_Mpl, ui->pb_Mmin,
        ui->pb_CE, ui->pbplmin, ui->pbpl, ui->pbmin, ui->pbpr, ui->pbdiv,
        ui->pbdot, ui->pbequal
    };

    for (QPushButton* button : buttons) {
        button->setEnabled(enabled);
    }
}

double MainWindow::evaluateExpression(const QString &expr, bool &ok)
{
    ok = true;
    QString e = expr;
    e.remove(' ');

    auto prec = [](QChar op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    };

    QVector<QString> output;
    QStack<QChar> ops;
    QString num;

    for (int i = 0; i < e.length(); ++i) {
        QChar c = e[i];

        if (c == '-' && (i == 0 || (!e[i - 1].isDigit() && e[i - 1] != ')'))) {
            num += c;
            continue;
        }

        if (c.isDigit() || c == '.') {
            num += c;
        } else {
            if (!num.isEmpty()) {
                output.append(num);
                num.clear();
            }

            while (!ops.isEmpty() && prec(ops.top()) >= prec(c)) {
                output.append(QString(ops.pop()));
            }
            ops.push(c);
        }
    }

    if (!num.isEmpty()) output.append(num);
    while (!ops.isEmpty()) output.append(QString(ops.pop()));

    QStack<double> stack;
    for (const QString &t : output) {
        if (t == "+" || t == "-" || t == "*" || t == "/") {
            if (stack.size() < 2) {
                ok = false;
                return 0;
            }
            double b = stack.pop();
            double a = stack.pop();

            if (t == "/" && b == 0) {
                ok = false;
                return 0;
            }

            if (t == "+") stack.push(a + b);
            else if (t == "-") stack.push(a - b);
            else if (t == "*") stack.push(a * b);
            else if (t == "/") stack.push(a / b);
        } else {
            bool convOk;
            double val = t.toDouble(&convOk);
            if (!convOk) {
                ok = false;
                return 0;
            }
            stack.push(val);
        }
    }

    if (stack.size() != 1) {
        ok = false;
        return 0;
    }

    return stack.top();
}
