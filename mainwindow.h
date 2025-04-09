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
    void on_digit_pushed();
    void on_operator_pushed();
    void on_equal_pushed();
    void on_dot_pushed();
    void on_inverse_pushed();
    void on_CE_pushed();
    void lclear();
    void on_mem_pushed();

private:
    Ui::MainWindow *ui;

    enum State {
        FirstDigit,
        InputNumber
    };

    State state;

    double first_number;
    double second_number;
    double mem;

    bool is_first_oper;
    bool after_operation;
    bool after_equal;
    bool mem_ok;

    QString prev_operation;
    QString equal_operation;

    void connectButtons();
    void calculate(double second_number, const QString &operation);
    void showMessage(const QString &msg);
};

#endif // MAINWINDOW_H
