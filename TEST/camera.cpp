#include "camera.h"
#include <QDebug>

Camera::Camera(QObject *parent) : QObject(parent)
{
}

void Camera::startCamera()
{
    qDebug() << "Caméra démarrée";
}

void Camera::stopCamera()
{
    qDebug() << "Caméra arrêtée";
}
