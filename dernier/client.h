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
    void sendMovementCommand(const QString &command);
    void sendCameraCommand(const QString &command);
    void sendGasSensorData(float gasValue);
    void sendMessage(const QString &message);
    void sendSensorData(const QString &sensorType, float value); // Nouvelle méthode
    void fetchData();

signals:
    void measurementsReceived(const QString &measurements);
    void sensorDataReceived(const QString &sensorType, float value); // New signal

private:
    QTcpSocket *socket; // Ajouter un socket pour la connexion
};

#endif // CLIENT_H
