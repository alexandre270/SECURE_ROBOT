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

    // Initialiser le label pour afficher les commandes
    commandLabel = new QLabel(this);
    commandLabel->setObjectName("commandLabel");

    ui->verticalLayout->addWidget(commandLabel); // Ajoutez le label à votre layout

    // Créer une instance de Client
    client = new Client(this);

    // Passer l'instance de Client à Server
    server = new Server(client, this);

    // Initialiser DBManager
    dbManager = new DBManager(this);

    // Démarrer le serveur ici
    startServer();

    // Initialiser Camera
    camera = new Camera(this);

    // Connexion mise à jour pour recevoir les données du capteur
    connect(client, &Client::sensorDataReceived, server, &Server::archiveSensorData);

    // Initialiser le flux vidéo
    videoStream = new VideoStream("udp://192.168.0.21:1234", this);
    connect(videoStream, &VideoStream::frameReady, this, &MainWindow::updateFrame);
    videoStream->start(); // Démarrer le flux vidéo
}

MainWindow::~MainWindow()
{
    // Libérer la mémoire des objets
    delete videoStream; // Libérer le flux vidéo
    delete camera; // Libérer la caméra
    delete server; // Libérer le serveur
    delete client; // Libérer le client
    delete dbManager; // Libérer le gestionnaire de base de données
    delete ui; // Libérer l'interface utilisateur
}

void MainWindow::startServer()
{
    tcpServer = new QTcpServer(this);

    QObject::connect(tcpServer, &QTcpServer::newConnection, [=]() {
        clientSocket = tcpServer->nextPendingConnection();
        qDebug() << "Client connecté !";

        QObject::connect(clientSocket, &QTcpSocket::readyRead, [=]() {
            QByteArray data = clientSocket->readAll();
            qDebug() << "Données reçues du client Flutter:" << QString(data);
        });

        QObject::connect(clientSocket, &QTcpSocket::disconnected, [=]() {
            qDebug() << "Client déconnecté.";
            clientSocket->deleteLater();
        });
    });

    if (!tcpServer->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Erreur d'écoute :" << tcpServer->errorString();
    } else {
        qDebug() << "Serveur en écoute sur le port 12345";
    }
}

void MainWindow::on_sendButton_clicked() {
    QString message = ui->messageLineEdit->text();
    client->sendMovementCommand(message); // Utilisez la méthode pour envoyer la commande
    ui->messagesTextEdit->append("Commande envoyée: " + message);

    // Mettre à jour le label avec la commande envoyée
    commandLabel->setText("Commande: " + message);
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

    // Mettre à jour le label avec la commande envoyée
    commandLabel->setText("Commande: " + command);
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

void MainWindow::on_captureScreenButton_clicked()
{
    // Capturer l'écran
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0);

    // Générer un nom de fichier avec la date et l'heure
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    QString filename = QString("capture_%1.png").arg(timestamp);

    // Sauvegarder la capture d'écran
    if (screenshot.save(filename)) {
        // Enregistrer le nom de fichier dans la base de données
        dbManager->insertSensorData("Capture d'écran", filename); // Passer le nom de fichier

        // Afficher un message dans le QTextEdit
        ui->commandsTextEdit->append("Capture d'écran sauvegardée: " + filename);
    } else {
        qDebug() << "Erreur lors de la sauvegarde de la capture d'écran.";
    }
}

void MainWindow::updateFrame(const QImage &image)
{
    ui->videoLabel->setPixmap(QPixmap::fromImage(image)); // Mettre à jour le QLabel avec l'image
}
