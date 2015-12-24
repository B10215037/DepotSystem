#include "userview.h"
#include "ui_userview.h"

UserView::UserView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserView)
{
    ui->setupUi(this);

    //LogInForm
    setForm(Form::Login, new LogInForm(this));
    connect((LogInForm*) forms[0], SIGNAL(logInSignal(QString,QString)),
            this, SLOT(logInSlot(QString,QString)));
    connect(this, SIGNAL(logInResult(QString)),
            (LogInForm*) forms[0], SLOT(showLogInResult(QString)));

    //CustomerMenu
    setForm(Form::CustomerMenu, new CustomerMenuForm(this));
    connect((CustomerMenuForm*) forms[1], SIGNAL(logOutSignal()),
            this, SLOT(logOutSlot()));

    //ManagerMenu
    setForm(Form::ManagerMenu, new ManagerMenuForm(this));
    connect((ManagerMenuForm*) forms[2], SIGNAL(getProductsInfoSignal()),
            this, SLOT(getProductsInfoSlot()));
    connect((ManagerMenuForm*) forms[2], SIGNAL(logOutSignal()),
                this, SLOT(logOutSlot()));

    //ProductManagement
    setForm(Form::ProductManagement, new ProductManagementForm(this));
    connect(this, SIGNAL(productManagementResult(QList<Product>)),
            (ProductManagementForm*) forms[3], SLOT(showProductManagementResult(QList<Product>)));

    //OrderManagement
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

void UserView::replyFinished(QNetworkReply* reply) {
    reply->deleteLater();
    while (widgetsRecycleList.size() != 0) delete widgetsRecycleList.takeAt(0);
    setEnabled(true);

    QString response;

    if (reply->error() != QNetworkReply::NoError) {
        response = reply->readAll();
        qDebug() << "\n[UserView::replyFinished] @ ERROR]" << reply->errorString() << response;

        QJsonObject object = QJsonDocument::fromJson(response.toUtf8()).object();
        switch (whichFormCallIndex) {
        case Form::Login:
            emit logInResult(reply->errorString() + "\n" + object["message"].toString());
            break;
        case Form::CustomerMenu:
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
        switch (whichFormCallIndex) {
        case Form::Login:
            if (object["message"].toString().split(" ")[0] == "admin") {
                emit changeWindow(Form::Login, Form::ManagerMenu);
                userName = "Admin:" + userName;
            }
            else {
                userName = "User:" + userName;
                emit changeWindow(Form::Login, Form::CustomerMenu);
            }
            emit logInResult("");
            break;
        case Form::CustomerMenu: {
            QJsonArray array = QJsonDocument::fromJson(response.toUtf8()).array();
            QList<Product> products;
            for (int i = 0; i < array.size(); i++) {
                Product product(array[i].toObject()["_id"].toString());
                product.setName(array[i].toObject()["name"].toString());
                product.setStock(array[i].toObject()["stock"].toInt());
                product.setPrice(array[i].toObject()["price"].toInt());
                products.append(product);
            }
            emit productManagementResult(products);
            break;
        }
        default:
            break;
        }
    }
}

void UserView::showLoadingDialog() {
    setEnabled(false);
    QDialog *dialog = new QDialog(this, Qt::CustomizeWindowHint);
    QLabel *content = new QLabel("Loading..." ,dialog);
    dialog->show();

    widgetsRecycleList.append(content);
    widgetsRecycleList.append(dialog);
}

void UserView::logInSlot(QString username, QString password) {
    showLoadingDialog();

    whichFormCallIndex = Form::Login;
    userName = username;

    connector->logIn(username, password);
}

void UserView::logOutSlot() {
    whichFormCallIndex = -1;

    connector->logOut();
}

void UserView::getProductsInfoSlot() {
    showLoadingDialog();

    if (userName.at(0) == 'A') whichFormCallIndex = Form::ManagerMenu;
    else whichFormCallIndex = -1;

    QList<Product> products;
    Product product("ID");
    products.append(product);

    connector->getProductsInfo();
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
}
