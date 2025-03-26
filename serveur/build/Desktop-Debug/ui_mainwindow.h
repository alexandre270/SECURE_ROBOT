/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *moveForwardButton;
    QPushButton *moveRightButton;
    QPushButton *moveLeftButton;
    QPushButton *moveBackwardButton;
    QTextEdit *measurementsOutput;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        moveForwardButton = new QPushButton(centralwidget);
        moveForwardButton->setObjectName(QString::fromUtf8("moveForwardButton"));
        moveForwardButton->setGeometry(QRect(260, 100, 88, 26));
        moveRightButton = new QPushButton(centralwidget);
        moveRightButton->setObjectName(QString::fromUtf8("moveRightButton"));
        moveRightButton->setGeometry(QRect(360, 160, 88, 26));
        moveLeftButton = new QPushButton(centralwidget);
        moveLeftButton->setObjectName(QString::fromUtf8("moveLeftButton"));
        moveLeftButton->setGeometry(QRect(130, 160, 88, 26));
        moveBackwardButton = new QPushButton(centralwidget);
        moveBackwardButton->setObjectName(QString::fromUtf8("moveBackwardButton"));
        moveBackwardButton->setGeometry(QRect(260, 220, 88, 26));
        measurementsOutput = new QTextEdit(centralwidget);
        measurementsOutput->setObjectName(QString::fromUtf8("measurementsOutput"));
        measurementsOutput->setGeometry(QRect(240, 30, 131, 41));
        measurementsOutput->setReadOnly(true);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        moveForwardButton->setText(QCoreApplication::translate("MainWindow", "Avancer", nullptr));
        moveRightButton->setText(QCoreApplication::translate("MainWindow", "Droite", nullptr));
        moveLeftButton->setText(QCoreApplication::translate("MainWindow", "Gauche", nullptr));
        moveBackwardButton->setText(QCoreApplication::translate("MainWindow", "Reculer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
