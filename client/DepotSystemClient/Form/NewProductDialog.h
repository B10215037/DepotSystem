#ifndef NEWPRODUCTDIALOG_H
#define NEWPRODUCTDIALOG_H

#include <QWidget>

namespace Ui {
class NewProductDialog;
}

class NewProductDialog : public QWidget
{
    Q_OBJECT

public:
    explicit NewProductDialog(QWidget *parent = 0);
    ~NewProductDialog();

signals:
    void confirmNewProduct(QString name, int stock, int price);
    void cancel();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::NewProductDialog *ui;
};

#endif // NEWPRODUCTDIALOG_H
