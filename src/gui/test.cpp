#include "../h/gui/test.h"

#include <QtGui>
#include <QMessageBox>

Test::Test(QWidget *parent) : QWidget(parent),
    ui(new Ui::testUi)
{
    ui->setupUi(this);
}

Test::~Test()
{

}

void Test::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("test");
    msgBox.setInformativeText("das isn test");
    msgBox.exec();
}
