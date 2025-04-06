/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_history;
    QLineEdit *leRes;
    QGridLayout *gridLayout;
    QPushButton *pb_MC;
    QPushButton *pb_MR;
    QPushButton *pb_MS;
    QPushButton *pb_Mpl;
    QPushButton *pb_Mmin;
    QPushButton *pb_CE;
    QPushButton *pb_C;
    QPushButton *pbplmin;
    QPushButton *pb_7;
    QPushButton *pb_8;
    QPushButton *pb_9;
    QPushButton *pbpl;
    QPushButton *pb_4;
    QPushButton *pb_5;
    QPushButton *pb_6;
    QPushButton *pbmin;
    QPushButton *pb_1;
    QPushButton *pb_2;
    QPushButton *pb_3;
    QPushButton *pbpr;
    QPushButton *pbdot;
    QPushButton *pb_0;
    QPushButton *pbequal;
    QPushButton *pbdiv;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(411, 315);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 322, 228));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lbl_history = new QLabel(widget);
        lbl_history->setObjectName("lbl_history");

        verticalLayout->addWidget(lbl_history);

        leRes = new QLineEdit(widget);
        leRes->setObjectName("leRes");
        leRes->setReadOnly(true);

        verticalLayout->addWidget(leRes);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        pb_MC = new QPushButton(widget);
        pb_MC->setObjectName("pb_MC");

        gridLayout->addWidget(pb_MC, 0, 0, 1, 1);

        pb_MR = new QPushButton(widget);
        pb_MR->setObjectName("pb_MR");

        gridLayout->addWidget(pb_MR, 0, 1, 1, 1);

        pb_MS = new QPushButton(widget);
        pb_MS->setObjectName("pb_MS");

        gridLayout->addWidget(pb_MS, 0, 2, 1, 1);

        pb_Mpl = new QPushButton(widget);
        pb_Mpl->setObjectName("pb_Mpl");

        gridLayout->addWidget(pb_Mpl, 0, 3, 1, 1);

        pb_Mmin = new QPushButton(widget);
        pb_Mmin->setObjectName("pb_Mmin");

        gridLayout->addWidget(pb_Mmin, 1, 0, 1, 1);

        pb_CE = new QPushButton(widget);
        pb_CE->setObjectName("pb_CE");

        gridLayout->addWidget(pb_CE, 1, 1, 1, 1);

        pb_C = new QPushButton(widget);
        pb_C->setObjectName("pb_C");

        gridLayout->addWidget(pb_C, 1, 2, 1, 1);

        pbplmin = new QPushButton(widget);
        pbplmin->setObjectName("pbplmin");

        gridLayout->addWidget(pbplmin, 1, 3, 1, 1);

        pb_7 = new QPushButton(widget);
        pb_7->setObjectName("pb_7");

        gridLayout->addWidget(pb_7, 2, 0, 1, 1);

        pb_8 = new QPushButton(widget);
        pb_8->setObjectName("pb_8");

        gridLayout->addWidget(pb_8, 2, 1, 1, 1);

        pb_9 = new QPushButton(widget);
        pb_9->setObjectName("pb_9");

        gridLayout->addWidget(pb_9, 2, 2, 1, 1);

        pbpl = new QPushButton(widget);
        pbpl->setObjectName("pbpl");

        gridLayout->addWidget(pbpl, 2, 3, 1, 1);

        pb_4 = new QPushButton(widget);
        pb_4->setObjectName("pb_4");

        gridLayout->addWidget(pb_4, 3, 0, 1, 1);

        pb_5 = new QPushButton(widget);
        pb_5->setObjectName("pb_5");

        gridLayout->addWidget(pb_5, 3, 1, 1, 1);

        pb_6 = new QPushButton(widget);
        pb_6->setObjectName("pb_6");

        gridLayout->addWidget(pb_6, 3, 2, 1, 1);

        pbmin = new QPushButton(widget);
        pbmin->setObjectName("pbmin");

        gridLayout->addWidget(pbmin, 3, 3, 1, 1);

        pb_1 = new QPushButton(widget);
        pb_1->setObjectName("pb_1");

        gridLayout->addWidget(pb_1, 4, 0, 1, 1);

        pb_2 = new QPushButton(widget);
        pb_2->setObjectName("pb_2");

        gridLayout->addWidget(pb_2, 4, 1, 1, 1);

        pb_3 = new QPushButton(widget);
        pb_3->setObjectName("pb_3");

        gridLayout->addWidget(pb_3, 4, 2, 1, 1);

        pbpr = new QPushButton(widget);
        pbpr->setObjectName("pbpr");

        gridLayout->addWidget(pbpr, 4, 3, 1, 1);

        pbdot = new QPushButton(widget);
        pbdot->setObjectName("pbdot");

        gridLayout->addWidget(pbdot, 5, 0, 1, 1);

        pb_0 = new QPushButton(widget);
        pb_0->setObjectName("pb_0");

        gridLayout->addWidget(pb_0, 5, 1, 1, 1);

        pbequal = new QPushButton(widget);
        pbequal->setObjectName("pbequal");

        gridLayout->addWidget(pbequal, 5, 2, 1, 1);

        pbdiv = new QPushButton(widget);
        pbdiv->setObjectName("pbdiv");

        gridLayout->addWidget(pbdiv, 5, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 411, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lbl_history->setText(QString());
        pb_MC->setText(QCoreApplication::translate("MainWindow", "MC", nullptr));
        pb_MR->setText(QCoreApplication::translate("MainWindow", "MR", nullptr));
        pb_MS->setText(QCoreApplication::translate("MainWindow", "MS", nullptr));
        pb_Mpl->setText(QCoreApplication::translate("MainWindow", "M+", nullptr));
        pb_Mmin->setText(QCoreApplication::translate("MainWindow", "M-", nullptr));
        pb_CE->setText(QCoreApplication::translate("MainWindow", "CE", nullptr));
        pb_C->setText(QCoreApplication::translate("MainWindow", "C", nullptr));
        pbplmin->setText(QCoreApplication::translate("MainWindow", "+-", nullptr));
        pb_7->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        pb_8->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        pb_9->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        pbpl->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
        pb_4->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        pb_5->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        pb_6->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        pbmin->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        pb_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pb_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        pb_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        pbpr->setText(QCoreApplication::translate("MainWindow", "*", nullptr));
        pbdot->setText(QCoreApplication::translate("MainWindow", ".", nullptr));
        pb_0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pbequal->setText(QCoreApplication::translate("MainWindow", "=", nullptr));
        pbdiv->setText(QCoreApplication::translate("MainWindow", "/", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
