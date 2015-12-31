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
        Form/LogInForm.cpp \
        Form/checkorderform.cpp \
        Form/singleorderform.cpp \
        Form/confirmorderform.cpp \
    Form/NewProductDialog.cpp \
    Form/modifyorderform.cpp

HEADERS += userview.h \
	Form/form.h \
	Form/customermenuform.h \
	Form/managermenuform.h \
	Form/productmanagementform.h \
	Form/ordermanagementform.h \
        Form/LogInForm.h \
        Form/checkorderform.h \
        Form/singleorderform.h \
        Form/confirmorderform.h \
    Form/NewProductDialog.h \
    Form/modifyorderform.h

FORMS   += userview.ui \
	Form/customermenuform.ui \
	Form/managermenuform.ui \
	Form/productmanagementform.ui \
	Form/ordermanagementform.ui \
        Form/LogInForm.ui \
        Form/checkorderform.ui \
        Form/singleorderform.ui \
        Form/confirmorderform.ui \
    Form/NewProductDialog.ui \
    Form/modifyorderform.ui
