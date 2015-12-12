#-------------------------------------------------
#
# Project created by QtCreator 2015-12-12T16:59:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Account
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
    Account.cpp \
    ManagerAccount.cpp \
    CustomerAccount.cpp

HEADERS  += mainwindow.h\
    Account.h \
    ManagerAccount.h \
    CustomerAccount.h

FORMS    += mainwindow.ui
