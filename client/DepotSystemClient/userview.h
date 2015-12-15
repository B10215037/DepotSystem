#ifndef USERVIEW_H
#define USERVIEW_H

#include <QMainWindow>
#include <QResizeEvent>
#include "Form/form.h"
#include "Form/loginform.h"
#include "Form/customermenuform.h"
#include "Form/managermenuform.h"
#include "Form/productmanagementform.h"
#include "Form/ordermanagementform.h"

namespace Ui {
class UserView;
}

class UserView : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserView(QWidget *parent = 0);
    ~UserView();

protected:
    void resizeEvent(QResizeEvent* event);
    void setForm(int formIndex, Form *form);

private:
    Ui::UserView *ui;
    Form* forms[Form::FORM_COUNT];

public slots:
    void changeWindow(int from, int to);
};

#endif // USERVIEW_H
