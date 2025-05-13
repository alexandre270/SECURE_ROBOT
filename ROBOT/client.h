#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QString>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void sendMovementCommand(const QString &command); // Pour envoyer des commandes au robot
    void sendDataToAndroid(const QString &data); // Pour envoyer des données à l'application Android

signals:
    void sensorDataReceived(const QString &sensorType, float value); // Nouveau signal pour les données du capteur

private:
    QTcpSocket *robotSocket; // Socket pour la connexion au robot
    QTcpSocket *androidSocket; // Socket pour la connexion à l'application Android
};

#endif // CLIENT_H
