#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class DBManager : public QObject
{
    Q_OBJECT

public:
    explicit DBManager(QObject *parent = nullptr);
    ~DBManager();

    bool connectToDatabase(const QString &host, const QString &databaseName, const QString &user, const QString &password);
    void disconnectFromDatabase();
    bool insertSensorData(const QString &sensorType, const QString &filename); // Changer float en QString
    QStringList fetchData(); // Nouvelle méthode pour récupérer les données

private:
    QSqlDatabase db; // Instance de la base de données
};

#endif // DBMANAGER_H
