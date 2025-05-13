#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    robotSocket = new QTcpSocket(this);
    androidSocket = new QTcpSocket(this);

    // Connexion au robot
    robotSocket->connectToHost("192.168.0.133", 12345); // Adresse IP du robot
    if (!robotSocket->waitForConnected(3000)) {
        qDebug() << "Erreur de connexion au robot:" << robotSocket->errorString();
    } else {
        qDebug() << "Client connecté au robot.";
    }

    // Connexion à l'application Android
    androidSocket->connectToHost("192.168.0.142", 12345); // Adresse IP de l'application Android
    if (!androidSocket->waitForConnected(3000)) {
        qDebug() << "Erreur de connexion à l'application Android:" << androidSocket->errorString();
    } else {
        qDebug() << "Client connecté à l'application Android.";
    }

    // Connecter le signal de réception de données
    connect(robotSocket, &QTcpSocket::readyRead, this, [this]() {
        QByteArray data = robotSocket->readAll();
        // Traitez les données reçues ici
        // Supposons que les données soient au format "sensorType:value"
        QStringList parts = QString(data).split(":");
        if (parts.size() == 2) {
            QString sensorType = parts[0];
            float value = parts[1].toFloat();
            emit sensorDataReceived(sensorType, value); // Émettre le signal
        }
    });
}

void Client::sendMovementCommand(const QString &command)
{
    if (robotSocket->state() == QAbstractSocket::ConnectedState) {
        robotSocket->write(command.toUtf8()); // Envoyer la commande au robot
        robotSocket->flush(); // Assurez-vous que les données sont envoyées
        qDebug() << "Commande envoyée au robot:" << command;
    } else {
        qDebug() << "Le client n'est pas connecté au robot.";
    }
}

void Client::sendDataToAndroid(const QString &data)
{
    if (androidSocket->state() == QAbstractSocket::ConnectedState) {
        androidSocket->write(data.toUtf8()); // Envoyer les données à l'application Android
        androidSocket->flush(); // Assurez-vous que les données sont envoyées
        qDebug() << "Données envoyées à l'application Android:" << data;
    } else {
        qDebug() << "Le client n'est pas connecté à l'application Android.";
    }
}
