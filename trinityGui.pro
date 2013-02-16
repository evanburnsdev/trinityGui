#-------------------------------------------------
#
# Project created by QtCreator 2013-02-10T16:43:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = trinityGui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    announcedialog.cpp \
    accountcdldialog.cpp \
    itemchooser.cpp

HEADERS  += mainwindow.h \
    announcedialog.h \
    accountcdldialog.h \
    itemchooser.h

FORMS    += \
    ../Designer/mainwindow.ui \
    ../Designer/announcedialog.ui \
    accountcdldialog.ui \
    itemchooser.ui

OTHER_FILES +=
