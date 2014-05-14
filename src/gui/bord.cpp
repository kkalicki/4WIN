#include "../h/gui/bord.h"
#include <QtGui>
#include <QLabel>
#include "h/gui/fourwinitemdelegate.h"

Bord::Bord(QWidget *parent, int rowCount, int colCount) : QWidget(parent),
    ui(new Ui::bordUi)
{
    ui->setupUi(this);
    this->defaultImage  = new QPixmap(":/image/def.png");
    this->redImage      = new QPixmap(":/image/red.png");
    this->yellowImage   = new QPixmap(":/image/yellow.png");
    this->rowCount      = rowCount;
    this->colCount      = colCount;
    init();
}

Bord::~Bord()
{
    delete ui;
    delete defaultImage;
    delete redImage;
    delete yellowImage;
}

void Bord::init()
{
    ui->tblbord->setColumnCount(colCount);
    ui->tblbord->setRowCount(rowCount);
    ui->tblbord->horizontalHeader()->setDefaultSectionSize(IMG_SIZE);
    ui->tblbord->verticalHeader()->setDefaultSectionSize(IMG_SIZE);
    ui->tblbord->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblbord->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblbord->setItemDelegate(new FourWinItemDelegate(ui->tblbord));

    for(int x = 0; x < rowCount; x++)
    {
        for(int y = 0; y < colCount; y++)
        {

            QTableWidgetItem *initItem = new QTableWidgetItem();
            initItem->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            initItem->setData(Qt::DecorationRole,defaultImage->scaled(IMG_SIZE,IMG_SIZE));
            ui->tblbord->setItem(x,y,initItem);
        }
    }
    this->resize(IMG_SIZE * colCount,IMG_SIZE * rowCount);

}

void Bord::on_tblbord_doubleClicked(const QModelIndex &index)
{
    QTableWidgetItem *initItem = new QTableWidgetItem();
    initItem->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
    initItem->setData(Qt::DecorationRole, redImage->scaled(IMG_SIZE,IMG_SIZE));
    ui->tblbord->setItem(index.row(),index.column(),initItem);
}
