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
    void on_fetchDataButton_clicked(); // Nouveau slot
    void on_startCameraButton_clicked(); // Nouveau slot
    void on_stopCameraButton_clicked(); // Nouveau slot
    void on_captureScreenButton_clicked(); // Nouveau slot
    void updateMeasurements(const QString &measurements);
    void updateFrame(const QImage &image); // Nouveau slot pour mettre à jour l'image de la caméra

private:
    Ui::MainWindow *ui;
    Client *client; // Pointeur vers l'objet Client
    Server *server; // Pointeur vers l'objet Server
    DBManager *dbManager; // Pointeur vers l'objet DBManager
    VideoStream *videoStream; // Pointeur vers l'objet VideoStream
    Camera *camera; // Pointeur vers l'objet Camera
};

#endif // MAINWINDOW_H
