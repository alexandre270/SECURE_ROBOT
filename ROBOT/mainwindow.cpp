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
    client = new Client(this); // Créer une instance de Client
    server = new Server(client, this); // Passer l'instance de Client à Server
    dbManager = new DBManager(this); // Initialiser DBManager
    server->startServer(); // Démarrer le serveur ici

    camera = new Camera(this); // Initialiser Camera

    // Connexion des boutons de l'interface utilisateur
    connect(ui->startCameraButton, &QPushButton::clicked, camera, &Camera::startCamera);
    connect(ui->stopCameraButton, &QPushButton::clicked, camera, &Camera::stopCamera);
    connect(client, &Client::sensorDataReceived, server, &Server::archiveSensorData); // Connexion mise à jour

    // Initialiser le flux vidéo
    videoStream = new VideoStream("udp://192.168.0.21:1234", this);
    connect(videoStream, &VideoStream::frameReady, this, &MainWindow::updateFrame);
    videoStream->start(); // Démarrer le flux vidéo
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked() {
    QString message = ui->messageLineEdit->text();
    client->sendMovementCommand(message); // Utilisez la méthode pour envoyer la commande
    ui->messagesTextEdit->append("Commande envoyée: " + message);
    ui->messageLineEdit->clear(); // Effacer le champ de saisie après l'envoi
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

void MainWindow::on_fetchDataButton_clicked()
{
    // Récupérer les données de la base de données
    QStringList data = dbManager->fetchData(); // Assurez-vous que cette méthode existe
    ui->measurementsTextEdit->clear(); // Effacer les anciennes données
    for (const QString &item : data) {
        ui->measurementsTextEdit->append(item); // Afficher chaque élément dans le QTextEdit
    }
}

void MainWindow::on_startCameraButton_clicked()
{
    camera->startCamera(); // Démarrer la caméra
}

void MainWindow::on_stopCameraButton_clicked()
{
    camera->stopCamera(); // Arrêter la caméra
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

    // Enregistrer le nom de fichier dans la base de données
    dbManager->insertSensorData("Capture d'écran", filename); // Passer le nom de fichier

    // Afficher un message dans le QTextEdit
    ui->commandsTextEdit->append("Capture d'écran sauvegardée: " + filename);
}

void MainWindow::updateFrame(const QImage &image)
{
    ui->videoLabel->setPixmap(QPixmap::fromImage(image)); // Mettre à jour le QLabel avec l'image
}
