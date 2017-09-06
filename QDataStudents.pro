#-------------------------------------------------
#
# Project created by QtCreator 2017-08-20T11:04:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QDataStudents
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialogaddstudent.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    dialogaddstudent.h \
    database.h

FORMS    += mainwindow.ui \
    dialogaddstudent.ui
