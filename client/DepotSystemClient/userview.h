#ifndef USERVIEW_H
#define USERVIEW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "Form/form.h"
#include "Form/LogInForm.h"
#include "Form/customermenuform.h"
#include "Form/managermenuform.h"
#include "Form/productmanagementform.h"
#include "Form/ordermanagementform.h"
#include "Form/checkorderform.h"
#include "Form/confirmorderform.h"
#include "Form/singleorderform.h"
#include "../Connector/Connector.h"
#include <QDialog>
#include <QLabel>
#include <QJsonObject>
#include "../Account/Account.h"

namespace Ui {
class UserView;
}

class UserView : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserView(QWidget *parent = 0);
    ~UserView();

    Connector *connector;

protected:
    void resizeEvent(QResizeEvent* event);
    void setForm(int formIndex, Form *form);

private:
    Ui::UserView *ui;
    Form *forms[Form::FORM_COUNT];
    QList<QWidget*> widgetsRecycleList;
    bool whichFormCallIndex;
    QString userName;

    void showLoadingDialog();

signals:
    void logInResult(QString message);
    void productManagementResult(QList<Product> products);

private slots:
    void changeWindow(int from, int to);

    void replyFinished(QNetworkReply* reply);
    void logInSlot(QString username, QString password);
    void logOutSlot();
    void getProductsInfoSlot();
};

#endif // USERVIEW_H
