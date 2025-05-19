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

bool DBManager::insertSensorData(const QString &sensorType, const QString &filename) // Changer float en QString
{
    QSqlQuery query;
    query.prepare("INSERT INTO mesures (type_capteur, valeur) VALUES (:type_capteur, :valeur)");
    query.bindValue(":type_capteur", sensorType);
    query.bindValue(":valeur", filename); // Changer float en QString

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'insertion des données:" << query.lastError().text();
        return false; // Échec de l'insertion
    }
    return true; // Insertion réussie
}

QStringList DBManager::fetchData()
{
    QStringList data;
    QSqlQuery query("SELECT type_capteur, valeur FROM mesures"); // Sélectionner les colonnes appropriées
    while (query.next()) {
        QString type = query.value(0).toString(); // Nom du capteur
        QString value = query.value(1).toString(); // Valeur du capteur
        data.append(QString("Nom: %1, Valeur: %2").arg(type).arg(value)); // Formatage des données
    }
    return data;
}
