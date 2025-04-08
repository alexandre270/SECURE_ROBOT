#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>

class DBManager : public QObject
{
    Q_OBJECT

public:
    explicit DBManager(QObject *parent = nullptr);
    bool openDatabase(const QString &host, const QString &user, const QString &password, const QString &dbName);
    QStringList fetchData();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
