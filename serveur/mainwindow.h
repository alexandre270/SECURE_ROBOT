#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void updateMeasurements(const QString &measurements);
    void on_moveButton_clicked();
    void on_cameraButton_clicked();
    void on_fetchButton_clicked();
    void on_sendGasButton_clicked();

private:
    Ui::MainWindow *ui;
    Client *client;
    Server *server;
};

#endif // MAINWINDOW_H
