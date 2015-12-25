#include "NewProductDialog.h"
#include "ui_NewProductDialog.h"
#include <QDebug>

NewProductDialog::NewProductDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProductDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);
}

NewProductDialog::NewProductDialog(QModelIndex index) :
    ui(new Ui::NewProductDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);

    ui->label->hide();
    ui->label_2->hide();
    ui->label_3->hide();
    ui->spinBox_2->hide();

    if (index.column() == 1) {
        ui->spinBox->hide();
        ui->lineEdit->setText(index.data().toString());
    }
    else {
        ui->lineEdit->setText(index.model()->index(index.row(), 1).data().toString());
        ui->lineEdit->hide();
        ui->spinBox->setValue(index.data().toInt());
    }
    modelIndex = index;
}

NewProductDialog::~NewProductDialog()
{
    delete ui;
}

void NewProductDialog::on_pushButton_clicked()
{
    if (ui->label->isHidden()) {
        QStandardItem *item =
                ((QStandardItemModel*) modelIndex.model())->item(modelIndex.row(),
                                                                 modelIndex.column());
        QString oldName;

        if (ui->lineEdit->isHidden()) {
            oldName = ui->lineEdit->text();
            item->setText(QString::number(ui->spinBox->value()));
        }
        else {
            oldName = item->text();
            item->setText(ui->lineEdit->text());
        }

        emit confirmEditedProduct(modelIndex, oldName);
    }
    else emit confirmNewProduct(ui->lineEdit->text(), ui->spinBox->value(), ui->spinBox_2->value());
    delete this;
}

void NewProductDialog::on_pushButton_2_clicked()
{
    emit cancel();
    delete this;
}
