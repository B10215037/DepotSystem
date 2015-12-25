#ifndef NEWPRODUCTDIALOG_H
#define NEWPRODUCTDIALOG_H

#include <QWidget>
#include <QStandardItemModel>

namespace Ui {
class NewProductDialog;
}

class NewProductDialog : public QWidget
{
    Q_OBJECT

public:
    explicit NewProductDialog(QWidget *parent = 0);
    explicit NewProductDialog(QModelIndex index);
    ~NewProductDialog();

signals:
    void confirmNewProduct(QString name, int stock, int price);
    void confirmEditedProduct(QModelIndex index, QString oldName);
    void cancel();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::NewProductDialog *ui;
    QModelIndex modelIndex;
};

#endif // NEWPRODUCTDIALOG_H
