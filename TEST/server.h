#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "client.h" // Inclure le fichier d'en-tête de Client

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(Client *client, QObject *parent = nullptr); // Ajouter le client en paramètre
    void startServer();

public slots:
    void archiveSensorData(const QString &sensorType, float value);

private slots:
    void onNewConnection();

private:
    QTcpServer *tcpServer;
    QSqlDatabase db; // Déclaration de la base de données
    Client *client; // Pointeur vers l'objet Client
};

#endif // SERVER_H
