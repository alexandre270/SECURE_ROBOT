#include "dbmanager.h"
#include <QDebug>

DBManager::DBManager(QObject *parent) : QObject(parent)
{
}

bool DBManager::openDatabase(const QString &host, const QString &user, const QString &password, const QString &dbName)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host); // Utiliser le paramètre hôte
    db.setUserName(user); // Utiliser le paramètre utilisateur
    db.setPassword(password); // Utiliser le paramètre mot de passe
    db.setDatabaseName(dbName); // Utiliser le paramètre nom de la base de données

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return false;
    }
    return true;
}

QStringList DBManager::fetchData()
{
    QStringList data;
    QSqlQuery query("SELECT type_capteur, valeur, date_enregistrement FROM mesures"); // Requête pour récupérer les données

    while (query.next()) {
        QString rowData = QString("Type: %1, Valeur: %2, Date: %3")
                              .arg(query.value(0).toString())
                              .arg(query.value(1).toString())
                              .arg(query.value(2).toString());
        data << rowData;
    }
    return data;
}
