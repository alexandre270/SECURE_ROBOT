#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QTcpServer>
#include <QImage>
#include <QBuffer>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void sendMovementCommand(const QString &command); // Pour envoyer des commandes au robot
    void sendDataToAndroid(const QString &data); // Pour envoyer des données à l'application Android

signals:
    void sensorDataReceived(const QString &sensorType, float value); // Signal pour les données du capteur

public slots:
    void readClientData(); // Déclaration de la méthode pour lire les données
    void handleVideoFrame(const QImage &image); // Ajout de la déclaration

private:
    QTcpSocket *robotSocket; // Socket pour la connexion au robot
    QTcpSocket *flutterSocket = nullptr;
    QTcpServer *server;
    char mapCommande(const QString &msg);
};

#endif // CLIENT_H
