#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTcpSocket>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToDatabase();
    void fetchData();
    void sendMessage(const QString &message);
    void sendMovementCommand(const QString &command);
    void sendCameraCommand(const QString &command);
    void sendGasSensorData(float value);

signals:
    void measurementsReceived(const QString &measurements); // Signal pour transmettre les mesures

private:
    QSqlDatabase db;
    QTcpSocket *socket;
};

#endif // CLIENT_H
