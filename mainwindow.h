// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void clicknum();
    void operatorClicked();
    void C();
    void CE();
    void on_pbdot_clicked();
    void changer();
    bool calc();
    void setButtonsEnabled(bool enabled);

private:
    Ui::MainWindow *ui;
    bool errorState = false;
    QString lastOperator;
    double lastOperand = 0;
    double lastResult = 0;
    bool hasLastOperation = false;
    bool wasJustEvaluated = false;
    bool newInputAfterEval = false;

    double evaluateExpression(const QString &expr, bool &ok);
};

#endif // MAINWINDOW_H
