#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
}

void Server::startServer()
{
    if (!server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Erreur de démarrage du serveur:" << server->errorString();
    } else {
        qDebug() << "Serveur démarré sur le port 1234.";
    }
}

void Server::onNewConnection()
{
    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
}

void Server::onReadyRead()
{
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        qDebug() << "Message reçu du client:" << data;
        emit measurementsReceived(QString(data));
    }
}

void Server::sendMessageToClient(const QString &message)
{
    if (clientSocket && clientSocket->state() == QTcpSocket::ConnectedState) {
        clientSocket->write(message.toUtf8());
        clientSocket->flush();
        qDebug() << "Message envoyé au client:" << message;
    } else {
        qDebug() << "Aucun client connecté pour envoyer le message.";
    }
}
