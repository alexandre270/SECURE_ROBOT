#include "server.h"
#include <QDebug>

Server::Server(QObject *parent) : QObject(parent)
{
}

void Server::startServer()
{
    // Connexion à la base de données MySQL
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // Hôte
    db.setUserName("Utilisateur"); // Nom d'utilisateur
    db.setPassword("Projet123!"); // Mot de passe
    db.setDatabaseName("mesures_robot"); // Nom de la base de données

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return; // Ne pas démarrer le serveur si la connexion échoue
    }

    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection, this, &Server::onNewConnection);

    // Écouter sur un port spécifique (changer le port si nécessaire)
    if (!tcpServer->listen(QHostAddress::Any, 12346)) { // Utiliser un port différent
        qDebug() << "Erreur de démarrage du serveur:" << tcpServer->errorString();
    } else {
        qDebug() << "Serveur démarré sur le port 12346";
    }
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();
    // Utilisez le clientSocket pour gérer la communication avec le client
    connect(clientSocket, &QTcpSocket::readyRead, [clientSocket]() {
        // Gérer les données entrantes du client
        QByteArray data = clientSocket->readAll();
        qDebug() << "Données reçues:" << data;
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
    }
}
