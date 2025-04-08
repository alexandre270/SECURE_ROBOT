#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "server.h"
#include "camera.h"
#include <QDebug>
#include <QDateTime>
#include <QScreen>
#include <QGuiApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client(this);
    server = new Server(this);
    server->startServer(); // Démarrer le serveur ici

    // Connexion des boutons de l'interface utilisateur
    Camera *camera = new Camera(this);
    connect(ui->startCameraButton, &QPushButton::clicked, camera, &Camera::startCamera);
    connect(ui->stopCameraButton, &QPushButton::clicked, camera, &Camera::stopCamera);
    connect(client, &Client::sensorDataReceived, server, &Server::archiveSensorData); // Connexion mise à jour
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();
    client->sendMessage(message);
    ui->messagesTextEdit->append("Message envoyé: " + message);
}

void MainWindow::updateMeasurements(const QString &measurements)
{
    ui->measurementsTextEdit->setPlainText(measurements);
}

void MainWindow::on_moveButton_clicked()
{
    QString command = ui->commandLineEdit->text();
    client->sendMovementCommand(command);
    ui->commandsTextEdit->append("Commande de mouvement envoyée: " + command);
}

void MainWindow::on_cameraButton_clicked()
{
    QString command = ui->cameraCommandLineEdit->text();
    client->sendCameraCommand(command);
    ui->commandsTextEdit->append("Commande de caméra envoyée: " + command);
}

void MainWindow::on_sendGasButton_clicked()
{
    float gasValue = 45.5; // Remplacez par la valeur réelle du capteur
    client->sendGasSensorData(gasValue);
    ui->commandsTextEdit->append("Données du capteur de gaz envoyées: " + QString::number(gasValue));
}

void MainWindow::on_fetchButton_clicked()
{
    // Cette méthode peut être supprimée si vous n'utilisez plus DBManager
    // QStringList data = dbManager->fetchData();
    // ui->measurementsTextEdit->clear(); // Effacer les anciennes données

    // for (const QString &item : data) {
    //     ui->measurementsTextEdit->append(item); // Afficher chaque élément dans le QTextEdit
    // }
}

void MainWindow::on_startCameraButton_clicked()
{
    qDebug() << "Démarrer la caméra"; // Logique pour démarrer la caméra
}

void MainWindow::on_stopCameraButton_clicked()
{
    qDebug() << "Arrêter la caméra"; // Logique pour arrêter la caméra
}

void MainWindow::on_captureScreenButton_clicked()
{
    // Capturer l'écran
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);

    // Générer un nom de fichier avec la date et l'heure
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString filename = QString("capture_%1.png").arg(timestamp);

    // Sauvegarder la capture d'écran
    screenshot.save(filename);

    // Afficher un message dans le QTextEdit
    ui->commandsTextEdit->append("Capture d'écran sauvegardée: " + filename);
}
