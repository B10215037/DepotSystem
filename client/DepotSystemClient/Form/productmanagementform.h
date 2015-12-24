#ifndef PRODUCTMANAGEMENTFORM_H
#define PRODUCTMANAGEMENTFORM_H

#include "form.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include "NewProductDialog.h"
#include "../Account/ManagerAccount.h"

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
    void on_pushButton_5_clicked();

    void showProductManagementResult(QList<Product> products);
    void addNewProduct(QString name, int stock, int price);
    void recycle();
    void recycleAndConfirmUpdate();

private:
    Ui::ProductManagementForm *ui;
    ManagerAccount account;
    QList<QWidget*> widgetRecycleContainer;

    void setTableView(QString id, QString name, int stock, int price);
};

#endif // PRODUCTMANAGEMENTFORM_H
