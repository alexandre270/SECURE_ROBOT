QT += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PROJET_backup
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           client.cpp \
           server.cpp \
           camera.cpp

HEADERS  += mainwindow.h \
             client.h \
             server.h \
             camera.h

FORMS    += mainwindow.ui
