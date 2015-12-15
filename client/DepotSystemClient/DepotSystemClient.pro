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
	Form/loginform.cpp \
	Form/customermenuform.cpp \
	Form/managermenuform.cpp \
	Form/productmanagementform.cpp \
	Form/ordermanagementform.cpp \

HEADERS += userview.h \
	Form/form.h \
	Form/loginform.h \
	Form/customermenuform.h \
	Form/managermenuform.h \
	Form/productmanagementform.h \
	Form/ordermanagementform.h

FORMS   += userview.ui \
	Form/loginform.ui \
	Form/customermenuform.ui \
	Form/managermenuform.ui \
	Form/productmanagementform.ui \
	Form/ordermanagementform.ui
