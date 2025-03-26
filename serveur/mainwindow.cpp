#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client(this);
    server = new Server(this);
    server->startServer();

    // Connecter le signal pour recevoir les mesures
    connect(client, &Client::measurementsReceived, this, &MainWindow::updateMeasurements);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString message = ui->messageLineEdit->text();  // Utiliser text() au lieu de toPlainText()
    client->sendMessage(message);  // Envoyer le message au serveur
}

void MainWindow::updateMeasurements(const QString &measurements)
{
    ui->measurementsTextEdit->setPlainText(measurements); // Mettre à jour le QTextEdit avec les mesures
}

void MainWindow::on_moveButton_clicked()
{
    QString command = ui->commandLineEdit->text();
    client->sendMovementCommand(command);
}

void MainWindow::on_cameraButton_clicked()
{
    QString command = ui->cameraCommandLineEdit->text();
    client->sendCameraCommand(command);
}

void MainWindow::on_fetchButton_clicked()
{
    client->fetchData(); // Récupérer les données lorsque le bouton est cliqué
}

void MainWindow::on_sendGasButton_clicked()
{
    float gasValue = 45.5; // Remplacez par la valeur réelle du capteur
    client->sendGasSensorData(gasValue); // Envoyer les données du capteur de gaz
}
