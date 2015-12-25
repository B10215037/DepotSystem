#include "NewProductDialog.h"
#include "ui_NewProductDialog.h"

NewProductDialog::NewProductDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NewProductDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint);
}

NewProductDialog::~NewProductDialog()
{
    delete ui;
}

void NewProductDialog::on_pushButton_clicked()
{
    emit confirmNewProduct(ui->lineEdit->text(), ui->spinBox->value(), ui->spinBox_2->value());
    delete this;
}

void NewProductDialog::on_pushButton_2_clicked()
{
    emit cancel();
    delete this;
}
