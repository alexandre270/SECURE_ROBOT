QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YourProjectName  # Remplacez par le nom de votre projet
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           server.cpp \
           client.cpp

HEADERS  += mainwindow.h \
            server.h \
            client.h

FORMS    += mainwindow.ui
