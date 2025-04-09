// dbmanager.cpp
#include "dbmanager.h"

DBManager::DBManager(QObject *parent) : QObject(parent)
{
    // Constructeur
}

DBManager::~DBManager()
{
    disconnectFromDatabase(); // Déconnexion à la base de données lors de la destruction
}

bool DBManager::connectToDatabase(const QString &host, const QString &databaseName, const QString &user, const QString &password)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setDatabaseName(databaseName);
    db.setUserName(user);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return false; // Échec de la connexion
    }
    qDebug() << "Connexion à la base de données réussie.";
    return true; // Connexion réussie
}

void DBManager::disconnectFromDatabase()
{
    if (db.isOpen()) {
        db.close();
        qDebug() << "Déconnexion de la base de données.";
    }
}

bool DBManager::insertSensorData(const QString &sensorType, float value)
{
    QSqlQuery query;
    query.prepare("INSERT INTO mesures (type_capteur, valeur) VALUES (:type_capteur, :valeur)");
    query.bindValue(":type_capteur", sensorType);
    query.bindValue(":valeur", value);

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion des données:" << query.lastError().text();
        return false; // Échec de l'insertion
    }
    return true; // Insertion réussie
}
