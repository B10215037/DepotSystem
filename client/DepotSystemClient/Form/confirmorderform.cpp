#include "confirmorderform.h"
#include "ui_confirmorderform.h"

ConfirmOrderForm::ConfirmOrderForm(QWidget *parent) :
    Form(parent),
    ui(new Ui::ConfirmOrderForm)
{
    ui->setupUi(this);
    dialog = new QDialog(this, Qt::Popup);
    confirmButton = new QPushButton(dialog);
    dialog->setSizeIncrement(QSize(200, 70));
    confirmButton->setGeometry(QRect(70, 20, 60, 30));
    confirmButton->setText("確認");
    connect(confirmButton, SIGNAL(clicked()),
            dialog, SLOT(done(int)));
}

ConfirmOrderForm::~ConfirmOrderForm()
{
    delete ui;
}

void ConfirmOrderForm::on_pushButton_2_clicked()
{
    changeWindow(ConfirmOrder, SingleOrder);
}

void ConfirmOrderForm::on_pushButton_clicked()
{
   	emit postOrdersInfoSignal(orderList);

    changeWindow(ConfirmOrder, CustomerMenu);
}

void ConfirmOrderForm::transferOrderSlot(QList<Item> items, QList<QString> names){

	QStandardItemModel *model = new QStandardItemModel(0, 2);
    model->setHorizontalHeaderItem(0, new QStandardItem("Name"));
    model->setHorizontalHeaderItem(1, new QStandardItem("Quantity"));
    ui->tableView->setModel(model);

    for (int i = 0; i < items.size(); i++) {
        QStandardItem *name = new QStandardItem(names[i]),
                	  *quantity = new QStandardItem(QString::number(items[i].amount));


        name->setEditable(false);
        quantity->setEditable(false);

        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 0, name);
        ((QStandardItemModel*) ui->tableView->model())->setItem(i, 1, quantity);
    }
    orderList = items;
}

void ConfirmOrderForm::showConfirmedDialog(){
//    setEnabled(false);
    QLabel *content = new QLabel("訂單已上傳" ,dialog);

    dialog->show();
}

void ConfirmOrderForm::showFailedDialog(){
//    setEnabled(false);
    QLabel *content = new QLabel("庫存不足" ,dialog);

    dialog->show();
}

void ConfirmOrderForm::postValid(bool valid){
	if(valid){
		showConfirmedDialog();
	}else{
        showFailedDialog();
	}
}
