#include "userview.h"
#include "ui_userview.h"

UserView::UserView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);

    setForm(Form::Login, new LogInForm(this));
    connect((LogInForm*) forms[0], SIGNAL(logInSignal(QString,QString)),
            this, SLOT(logInSlot(QString,QString)));
    connect(this, SIGNAL(logInResult(bool,QString)),
            (LogInForm*) forms[0], SLOT(showLogInResult(bool,QString)));

    setForm(Form::CustomerMenu, new CustomerMenuForm(this));
    connect((CustomerMenuForm*) forms[1], SIGNAL(logOutSignal()),
            this, SLOT(logOutSlot()));

    setForm(Form::ManagerMenu, new ManagerMenuForm(this));
    connect((ManagerMenuForm*) forms[2], SIGNAL(logOutSignal()),
            this, SLOT(logOutSlot()));

    setForm(Form::ProductManagement, new ProductManagementForm(this));
    setForm(Form::OrderManagement, new OrderManagementForm(this));
    forms[Form::Login]->show();

    connector = new Connector();
    connect(connector, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));

    setForm(Form::CheckOrder, new CheckOrderForm(this));
    setForm(Form::ConfirmOrder, new ConfirmOrderForm(this));
    setForm(Form::SingleOrder, new SingleOrderForm(this));
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

void UserView::showMessage(const QString &text, int timeout = 0)
{
    ui->statusBar->showMessage(text, timeout);
}

void UserView::replyFinished(QNetworkReply* reply) {
    reply->deleteLater();
    while (widgetsRecycleList.size() != 0) delete widgetsRecycleList.takeAt(0);
    setEnabled(true);

    QString response;

    if (reply->error() != QNetworkReply::NoError) {
        response = reply->readAll();
//        qDebug() << "\n[UserView::replyFinished] @ ERROR]" << reply->errorString() << response;

        QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
        switch (whichFormCallIndex) {
        case 0:
            emit logInResult(true, object["message"].toString());
            break;
        default:
            break;
        }
    }
    else if (reply->isReadable()) {
        QList<QNetworkCookie> cookies =
                qvariant_cast< QList<QNetworkCookie> >(reply->header(QNetworkRequest::SetCookieHeader));
        qDebug() << "\n[UserView::replyFinished] @ COOKIES]" << cookies;

        if(cookies.count() != 0) connector->cookieJar()->setCookiesFromUrl(cookies, reply->request().url());

        response = reply->readAll();
        printf("\n[UserView::replyFinished @ DATA] %s\n", response.toUtf8().data());
        fflush(stdout);

        QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
        user = new Account(tempUsername);
        switch (whichFormCallIndex) {
        case 0:
            emit logInResult(false, object["message"].toString().split(" ")[0]);
            break;
        default:
            break;
        }
    }
}

void UserView::logInSlot(QString username, QString password) {
    setEnabled(false);
    QDialog *dialog = new QDialog(this, Qt::CustomizeWindowHint);
    QLabel *content = new QLabel("Loading..." ,dialog);
    widgetsRecycleList.append(content);
    widgetsRecycleList.append(dialog);
    dialog->setEnabled(false);
    dialog->show();

    whichFormCallIndex = 0;
    tempUsername = username;

    connector->logIn(username, password);
}

void UserView::logOutSlot() {
    whichFormCallIndex = 1;

    connector->logOut();
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
    connect(forms[formIndex], SIGNAL(changeWindow(int,int)),
            this, SLOT(changeWindow(int,int)));
    connect(forms[formIndex], SIGNAL(showMessage(QString,int)),
            this, SLOT(showMessage(QString,int)));
}
