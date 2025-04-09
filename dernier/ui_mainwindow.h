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
    QLineEdit *cameraCommandLineEdit;
    QPushButton *cameraButton;
    QPushButton *sendGasButton;
    QTextEdit *measurementsTextEdit;
    QPushButton *startCameraButton;
    QPushButton *stopCameraButton;
    QPushButton *fetchButton;
    QPushButton *captureScreenButton;
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

        cameraCommandLineEdit = new QLineEdit(centralwidget);
        cameraCommandLineEdit->setObjectName(QString::fromUtf8("cameraCommandLineEdit"));

        verticalLayout->addWidget(cameraCommandLineEdit);

        cameraButton = new QPushButton(centralwidget);
        cameraButton->setObjectName(QString::fromUtf8("cameraButton"));

        verticalLayout->addWidget(cameraButton);

        sendGasButton = new QPushButton(centralwidget);
        sendGasButton->setObjectName(QString::fromUtf8("sendGasButton"));

        verticalLayout->addWidget(sendGasButton);

        measurementsTextEdit = new QTextEdit(centralwidget);
        measurementsTextEdit->setObjectName(QString::fromUtf8("measurementsTextEdit"));
        measurementsTextEdit->setReadOnly(true);

        verticalLayout->addWidget(measurementsTextEdit);

        startCameraButton = new QPushButton(centralwidget);
        startCameraButton->setObjectName(QString::fromUtf8("startCameraButton"));

        verticalLayout->addWidget(startCameraButton);

        stopCameraButton = new QPushButton(centralwidget);
        stopCameraButton->setObjectName(QString::fromUtf8("stopCameraButton"));

        verticalLayout->addWidget(stopCameraButton);

        fetchButton = new QPushButton(centralwidget);
        fetchButton->setObjectName(QString::fromUtf8("fetchButton"));

        verticalLayout->addWidget(fetchButton);

        captureScreenButton = new QPushButton(centralwidget);
        captureScreenButton->setObjectName(QString::fromUtf8("captureScreenButton"));

        verticalLayout->addWidget(captureScreenButton);

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
        cameraCommandLineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "Entrez votre commande de cam\303\251ra ici", nullptr));
        cameraButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Commande de Cam\303\251ra", nullptr));
        sendGasButton->setText(QCoreApplication::translate("MainWindow", "Envoyer Donn\303\251es de Gaz", nullptr));
        startCameraButton->setText(QCoreApplication::translate("MainWindow", "D\303\251marrer Cam\303\251ra", nullptr));
        stopCameraButton->setText(QCoreApplication::translate("MainWindow", "Arr\303\252ter Cam\303\251ra", nullptr));
        fetchButton->setText(QCoreApplication::translate("MainWindow", "R\303\251cup\303\251rer Donn\303\251es", nullptr));
        captureScreenButton->setText(QCoreApplication::translate("MainWindow", "Capturer \303\211cran", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
