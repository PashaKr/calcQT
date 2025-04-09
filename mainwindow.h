#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void digitClicked();
    void operatorClicked();
    void equalClicked();
    void decimalClicked();
    void signChanged();
    void clearEntry();
    void clearAll();
    void memoryOperation();

private:
    Ui::MainWindow *ui;

    enum State {
        FirstDigit,
        InputNumber
    };

    State currentState;
    double firstNumber;
    double secondNumber;
    double memoryValue;
    QString currentOperation;
    QString pendingOperation;

    bool isFirstOperation;
    bool afterOperation;
    bool afterEqual;
    bool memoryEnabled;
    bool errorOccurred;

    void initializeCalculator();
    void connectButtons();
    void calculate(double operand, const QString &operation);
    void updateDisplay(double value);
    void showError(const QString &message);
};

#endif // MAINWINDOW_H
