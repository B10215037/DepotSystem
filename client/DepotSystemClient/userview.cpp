#include "userview.h"
#include "ui_userview.h"

UserView::UserView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);
    setForm(Form::Login, new LoginForm(this));
    setForm(Form::CustomerMenu, new CustomerMenuForm(this));
    setForm(Form::ManagerMenu, new ManagerMenuForm(this));
    setForm(Form::ProductManagement, new ProductManagementForm(this));
    setForm(Form::OrderManagement, new OrderManagementForm(this));
    forms[Form::Login]->show();
}

UserView::~UserView()
{
    delete ui;
}

void UserView::changeWindow(int from, int to)
{
    forms[from]->hide();
    forms[to]->show();
}

void UserView::resizeEvent(QResizeEvent* event)
{
    for (int i = 0; i < Form::FORM_COUNT; i++) {
        forms[i]->resize(event->size());
    }
}

void UserView::setForm(int formIndex, Form *form)
{
    forms[formIndex] = form;
    forms[formIndex]->hide();
    QObject::connect(forms[formIndex], SIGNAL(changeWindow(int,int)), this, SLOT(changeWindow(int,int)));
}
