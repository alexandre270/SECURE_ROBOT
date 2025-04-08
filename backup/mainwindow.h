#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "client.h"
#include "server.h"
#include "camera.h"
#include "dbmanager.h" // Inclure DBManager

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_moveButton_clicked();
    void on_cameraButton_clicked();
    void on_fetchButton_clicked();
    void on_sendGasButton_clicked();
    void on_startCameraButton_clicked();
    void on_stopCameraButton_clicked();
    void updateMeasurements(const QString &measurements);
    void on_captureScreenButton_clicked(); // Nouveau slot pour le bouton de capture d'écran

private:
    Ui::MainWindow *ui;
    Client *client;
    Server *server;
    DBManager *dbManager; // Ajouter DBManager ici
};

#endif // MAINWINDOW_H
