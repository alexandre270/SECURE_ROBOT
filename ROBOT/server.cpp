#include "server.h"
#include <QDebug>

Server::Server(Client *client, QObject *parent) : QObject(parent), client(client) // Initialiser le client
{
}

void Server::startServer()
{
    // Connexion à la base de données MySQL
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("Utilisateur");
    db.setPassword("Projet123!");
    db.setDatabaseName("mesures_robot");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return; // Ne pas démarrer le serveur si la connexion échoue
    }

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);

    // Écouter sur un port spécifique
    if (!tcpServer->listen(QHostAddress::Any, 12345)) { // Utiliser le port 12345 pour le serveur
        qDebug() << "Erreur de démarrage du serveur:" << tcpServer->errorString();
    } else {
        qDebug() << "Serveur démarré sur le port 12345";
    }
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, [this, clientSocket]() {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Données reçues:" << data;

        // Traitez la commande reçue
        if (data.startsWith("MOUVEMENT:")) {
            QString command = data.mid(10); // Extraire la commande
            qDebug() << "Commande de mouvement reçue:" << command;
            client->sendMovementCommand(command); // Envoyer la commande au robot
        }
    });
}

void Server::archiveSensorData(const QString &sensorType, float value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO mesures (type_capteur, valeur) VALUES (:type_capteur, :valeur)");
    query.bindValue(":type_capteur", sensorType);
    query.bindValue(":valeur", value);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'archivage des données:" << query.lastError().text();
    } else {
        // Envoyer les données à l'application Android
        QString data = QString("Type: %1, Valeur: %2").arg(sensorType).arg(value);
        client->sendDataToAndroid(data); // Envoyer les données à l'application Android
    }
}
