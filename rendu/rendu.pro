# Project file for the Qt application

QT       += core gui sql network  # Added sql and network modules
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rendu
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           videostream.cpp \
           server.cpp \
           client.cpp \
           camera.cpp \
           dbmanager.cpp

HEADERS  += mainwindow.h \
            videostream.h \
            server.h \
            client.h \
            camera.h \
            dbmanager.h

FORMS    += mainwindow.ui

# Include paths for FFmpeg
INCLUDEPATH += /usr/include/ffmpeg

# Link against FFmpeg libraries
LIBS += -lavformat -lavcodec -lavutil -lswscale

# Additional configurations
# If you are using MySQL, you may need to link against the MySQL library
# LIBS += -lmysqlclient

# Add any other necessary configurations or libraries here
