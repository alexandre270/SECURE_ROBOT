#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connectToDatabase();
    socket = new QTcpSocket(this);
}

void Client::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mesures_robot");
    db.setUserName("Utilisateur");
    db.setPassword("Projet123!");

    if (!db.open()) {
        qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
    } else {
        qDebug() << "Connexion réussie à la base de données.";
        fetchData(); // Récupération des données après connexion
    }
}

void Client::fetchData()
{
    QSqlQuery query(db);
    query.prepare("SELECT * FROM mesures");

    if (!query.exec()) {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        return;
    }

    QString measurements;
    while (query.next()) {
        int id = query.value("id").toInt();
        QString type_capteur = query.value("type_capteur").toString();
        double valeur = query.value("valeur").toDouble();
        QString date_enregistrement = query.value("date_enregistrement").toString();

        measurements += QString("ID: %1 | Type: %2 | Valeur: %3 | Date: %4\n")
                            .arg(id)
                            .arg(type_capteur)
                            .arg(valeur)
                            .arg(date_enregistrement);
    }

    emit measurementsReceived(measurements); // Émettre les mesures récupérées
}

void Client::sendMessage(const QString &message)
{
    socket->connectToHost("localhost", 1234);

    if (socket->waitForConnected()) {
        socket->write(message.toUtf8());
        socket->flush();
        socket->waitForBytesWritten();
        socket->disconnectFromHost();
        qDebug() << "Message envoyé au serveur:" << message;
    } else {
        qDebug() << "Erreur de connexion au serveur.";
    }
}

void Client::sendMovementCommand(const QString &command)
{
    sendMessage(command);
    qDebug() << "Commande de déplacement envoyée:" << command;
}

void Client::sendCameraCommand(const QString &command)
{
    sendMessage(command);
    qDebug() << "Commande de caméra envoyée:" << command;
}

void Client::sendGasSensorData(float value)
{
    QString message = QString("MQ Gas Sensor: %1").arg(value);
    sendMessage(message);
}
