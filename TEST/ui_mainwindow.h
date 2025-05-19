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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *videoLabel;
    QLineEdit *messageLineEdit;
    QPushButton *sendButton;
    QTextEdit *messagesTextEdit;
    QLineEdit *commandLineEdit;
    QPushButton *moveButton;
    QTextEdit *commandsTextEdit;
    QPushButton *fetchDataButton;
    QPushButton *captureScreenButton;
    QTextEdit *measurementsTextEdit;
    QLabel *commandLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videoLabel = new QLabel(centralwidget);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        videoLabel->setMinimumSize(QSize(640, 480));

        verticalLayout->addWidget(videoLabel);

        messageLineEdit = new QLineEdit(centralwidget);
        messageLineEdit->setObjectName(QString::fromUtf8("messageLineEdit"));

        verticalLayout->addWidget(messageLineEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout->addWidget(sendButton);

        messagesTextEdit = new QTextEdit(centralwidget);
        messagesTextEdit->setObjectName(QString::fromUtf8("messagesTextEdit"));
        messagesTextEdit->setReadOnly(true);

        verticalLayout->addWidget(messagesTextEdit);

        commandLineEdit = new QLineEdit(centralwidget);
        commandLineEdit->setObjectName(QString::fromUtf8("commandLineEdit"));

        verticalLayout->addWidget(commandLineEdit);

        moveButton = new QPushButton(centralwidget);
        moveButton->setObjectName(QString::fromUtf8("moveButton"));

        verticalLayout->addWidget(moveButton);

        commandsTextEdit = new QTextEdit(centralwidget);
        commandsTextEdit->setObjectName(QString::fromUtf8("commandsTextEdit"));
        commandsTextEdit->setReadOnly(true);

        verticalLayout->addWidget(commandsTextEdit);

        fetchDataButton = new QPushButton(centralwidget);
        fetchDataButton->setObjectName(QString::fromUtf8("fetchDataButton"));

        verticalLayout->addWidget(fetchDataButton);

        captureScreenButton = new QPushButton(centralwidget);
        captureScreenButton->setObjectName(QString::fromUtf8("captureScreenButton"));

        verticalLayout->addWidget(captureScreenButton);

        measurementsTextEdit = new QTextEdit(centralwidget);
        measurementsTextEdit->setObjectName(QString::fromUtf8("measurementsTextEdit"));
        measurementsTextEdit->setReadOnly(true);

        verticalLayout->addWidget(measurementsTextEdit);

        commandLabel = new QLabel(centralwidget);
        commandLabel->setObjectName(QString::fromUtf8("commandLabel"));

        verticalLayout->addWidget(commandLabel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mon Application", nullptr));
        videoLabel->setText(QCoreApplication::translate("MainWindow", "Flux Vid\303\251o", nullptr));
        messageLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre message ici", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Message", nullptr));
        commandLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre commande de mouvement ici", nullptr));
        moveButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Commande de Mouvement", nullptr));
        fetchDataButton->setText(QCoreApplication::translate("MainWindow", "R\303\251cup\303\251rer Donn\303\251es", nullptr));
        captureScreenButton->setText(QCoreApplication::translate("MainWindow", "Capturer \303\211cran", nullptr));
        commandLabel->setText(QCoreApplication::translate("MainWindow", "Q - Tourner \303\240 gauche, X - Arr\303\252ter moteurs, D - Tourner \303\240 droite, S - Reculer, A - Tours, W - Recule \303\240 gauche, C - Recule \303\240 droite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
