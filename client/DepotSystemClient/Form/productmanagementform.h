#ifndef PRODUCTMANAGEMENTFORM_H
#define PRODUCTMANAGEMENTFORM_H

#include "form.h"
#include "NewProductDialog.h"
#include "../Account/ManagerAccount.h"
#include <QMessageBox>

namespace Ui {
class ProductManagementForm;
}

class ProductManagementForm : public Form
{
    Q_OBJECT

public:
    explicit ProductManagementForm(QWidget *parent = 0);
    ~ProductManagementForm();

signals:
    void updateProductsSignal(QList<Product> newProducts,
                              QList<Product> changedProducts,
                              QList<Product> deletedProducts);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

    void addNewProduct(QString name, int stock, int price);
    void editProduct(QModelIndex index, QString oldName);
    void tableItemChanged(QModelIndex index);
    void recycle();
    void recycleAndConfirmUpdate();
    void showProductManagementResult(QList<Product> products);

private:
    Ui::ProductManagementForm *ui;
    ManagerAccount account;
    QList<QWidget*> widgetRecycleContainer;

    void setTableView(QString id, QString name, int stock, int price);
};

#endif // PRODUCTMANAGEMENTFORM_H
