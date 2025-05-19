#include "client.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QImage>
#include <QBuffer>

Client::Client(QObject *parent) : QObject(parent)
{
    // === Connexion au robot ===
    robotSocket = new QTcpSocket(this);
    robotSocket->connectToHost("192.168.0.133", 12345); // Adresse IP du robot
    if (!robotSocket->waitForConnected(3000)) {
        qDebug() << "Erreur de connexion au robot:" << robotSocket->errorString();
    } else {
        qDebug() << "Client connecté au robot.";
    }

    // === Lancement du serveur pour accepter la connexion de Flutter ===
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, [this]() {
        flutterSocket = server->nextPendingConnection();
        qDebug() << "Client Flutter connecté !";

        // Connecte la réception des données de Flutter
        connect(flutterSocket, &QTcpSocket::readyRead, this, &Client::readClientData);
    });

    if (!server->listen(QHostAddress::Any, 12345)) {
        qDebug() << "Erreur d'écoute :" << server->errorString();
    } else {
        qDebug() << "Serveur en écoute sur le port 12345";
    }

    // === Réception de données du robot ===
    connect(robotSocket, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = robotSocket->readAll();
        QStringList parts = QString(data).split(":");
        if (parts.size() == 2) {
            QString sensorType = parts[0];
            float value = parts[1].toFloat();
            emit sensorDataReceived(sensorType, value);
        }
    });
}

void Client::handleVideoFrame(const QImage &image) {
    if (flutterSocket && flutterSocket->state() == QAbstractSocket::ConnectedState) {
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "JPEG");

        QString base64Image = QString::fromLatin1(byteArray.toBase64());
        QString message = "{\"video\":\"" + base64Image + "\"}\n";

        flutterSocket->write(message.toUtf8());
        flutterSocket->flush();
    }
}

char Client::mapCommande(const QString &msg)
{
    if (msg == "move_forward") return 'Z';
    if (msg == "move_backward") return 'S';
    if (msg == "move_forward_left") return 'Q';
    if (msg == "move_forward_right") return 'D';
    if (msg == "stop") return 'X';
    if (msg == "rotation") return 'A';
    if (msg == "move_backward_left") return 'W';
    if (msg == "move_backward_right") return 'C';
    return 'X'; // Par défaut = stop
}

void Client::sendMovementCommand(const QString &command)
{
    if (robotSocket->state() == QAbstractSocket::ConnectedState) {
        robotSocket->write(command.toUtf8());
        robotSocket->flush();
        qDebug() << "Commande envoyée au robot:" << command;
    } else {
        qDebug() << "Le client n'est pas connecté au robot.";
    }
}

void Client::readClientData()
{
    if (!flutterSocket) return;

    QByteArray data = flutterSocket->readAll();
    QString message = QString(data).trimmed();
    qDebug() << "Reçu de Flutter:" << message;

    // Ne pas envoyer "connect" ou "disconnect" au robot
    if (message != "connect" && message != "disconnect") {
        if (robotSocket && robotSocket->isOpen()) {
            char commande = mapCommande(message);
            robotSocket->write(&commande, 1);
            robotSocket->flush();
            qDebug() << "Envoyé au robot:" << commande;
        } else {
            qDebug() << " robotSocket non connecté.";
        }
    }

    // Réponse à Flutter
    QString response = "OK:" + message + "\n";
    flutterSocket->write(response.toUtf8());
    flutterSocket->flush();
}

void Client::sendDataToAndroid(const QString &data)
{
    if (flutterSocket && flutterSocket->state() == QAbstractSocket::ConnectedState) {
        flutterSocket->write(data.toUtf8());
        flutterSocket->flush();
        qDebug() << "Données envoyées à Flutter:" << data;
    } else {
        qDebug() << "Flutter n'est pas connecté.";
    }
}
