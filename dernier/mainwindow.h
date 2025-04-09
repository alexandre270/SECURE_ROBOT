#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include "client.h"
#include "server.h"
#include "camera.h"
#include "videostream.h"
#include "dbmanager.h" // Inclure le fichier d'en-tête de DBManager

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
    void on_captureScreenButton_clicked();
    void updateFrame(const QImage &image); // Nouveau slot pour mettre à jour l'image de la caméra

private:
    Ui::MainWindow *ui;
    Client *client;
    Server *server;
    DBManager *dbManager; // Pointeur vers l'objet DBManager
    VideoStream *videoStream; // Pointeur vers l'objet VideoStream
};

#endif // MAINWINDOW_H
