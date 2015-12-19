#-------------------------------------------------
#
# Project created by QtCreator 2015-12-13T16:30:39
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DepotSystemClient
TEMPLATE = app

include(IncludeClass.pri)

SOURCES += main.cpp\
		userview.cpp \
	Form/form.cpp \
	Form/customermenuform.cpp \
	Form/managermenuform.cpp \
	Form/productmanagementform.cpp \
	Form/ordermanagementform.cpp \
        Form/LogInForm.cpp

HEADERS += userview.h \
	Form/form.h \
	Form/customermenuform.h \
	Form/managermenuform.h \
	Form/productmanagementform.h \
	Form/ordermanagementform.h \
        Form/LogInForm.h

FORMS   += userview.ui \
	Form/customermenuform.ui \
	Form/managermenuform.ui \
	Form/productmanagementform.ui \
	Form/ordermanagementform.ui \
        Form/LogInForm.ui
