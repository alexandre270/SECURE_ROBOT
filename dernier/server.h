#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer();

public slots:
    void archiveSensorData(const QString &sensorType, float value);

private slots:
    void onNewConnection();

private:
    QTcpServer *tcpServer;
    QSqlDatabase db; // Déclaration de la base de données
};

#endif // SERVER_H
