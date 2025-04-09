#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    // Replace with the actual IP address of the server
    socket->connectToHost("192.168.1.100", 12345); // Example IP address of the server
}

void Client::sendMovementCommand(const QString &command)
{
    qDebug() << "Commande de mouvement envoyée: " << command;
}

void Client::sendCameraCommand(const QString &command)
{
    qDebug() << "Commande de caméra envoyée: " << command;
}

void Client::sendGasSensorData(float gasValue)
{
    qDebug() << "Donnée de capteur de gaz envoyée: " << gasValue;
}

void Client::sendMessage(const QString &message)
{
    qDebug() << "Message envoyé: " << message;
}

void Client::sendSensorData(const QString &sensorType, float value) // Nouvelle méthode
{
    qDebug() << "Donnée de capteur envoyée: " << sensorType << " - " << value;
    emit sensorDataReceived(sensorType, value); // Emit the new signal
}

void Client::fetchData()
{
    qDebug() << "Récupération des données demandée";
}
