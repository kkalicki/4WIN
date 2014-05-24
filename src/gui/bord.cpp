#include "../h/gui/bord.h"
#include "../h/gui/fourwinitemdelegate.h"
#include "../h/sys/Konstanten.h"
#include <QtGui>
#include <QLabel>
#include <QMessageBox>

Bord::Bord(unsigned short rowCount, unsigned short colCount, unsigned short cellSize, QWidget *parent) : QWidget(parent),
    ui(new Ui::bordUi)
{
    ui->setupUi(this);
    this->defaultImage  = new QPixmap(":/image/border_new.png");
    this->redImage      = new QPixmap(":/image/red_new.png");
    this->yellowImage   = new QPixmap(":/image/yellow_new2.png");
    this->rowCount      = rowCount;
    this->colCount      = colCount;
    this->cellSize      = cellSize;
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
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);

    ui->tblbord->setColumnCount(colCount);
    ui->tblbord->setRowCount(rowCount);
    ui->tblbord->horizontalHeader()->setDefaultSectionSize(cellSize);
    ui->tblbord->verticalHeader()->setDefaultSectionSize(cellSize);
    ui->tblbord->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblbord->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tblbord->setItemDelegate(new FourWinItemDelegate(ui->tblbord));

    for(int x = 0; x < rowCount; x++){
        for(int y = 0; y < colCount; y++){

            QTableWidgetItem *initItem = new QTableWidgetItem();
            initItem->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
            initItem->setData(Qt::DecorationRole,defaultImage->scaled(cellSize,cellSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
            ui->tblbord->setItem(x,y,initItem);
        }
    }
    int w = cellSize * colCount;
    int h = cellSize * rowCount;
    this->resize(w,h);
    this->setFixedSize(w,h);
    this->show();
    isLocked=true;
}

void Bord::clear()
{
    for(int x = 0; x < rowCount; x++){
        for(int y = 0; y < colCount; y++){
               delete ui->tblbord->item(x,y);
        }
    }
}

void Bord::setMove(Spieler player, int row, int col)
{
    row = rowCount - row--;
    col--;
    delete ui->tblbord->item(row,col);
    QTableWidgetItem *initItem = new QTableWidgetItem();
    initItem->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);

    switch (player.getFarbe()) {
    case ROT:
        initItem->setData(Qt::DecorationRole, redImage->scaled(cellSize,cellSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    case GELB:
        initItem->setData(Qt::DecorationRole, yellowImage->scaled(cellSize,cellSize,Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        break;
    default:
            //kann ned sinn...!!
        break;
    }
    ui->tblbord->setItem(row,col,initItem);
}

void Bord::preExecute()
{
    isLocked = false;
}

void Bord::postExecute()
{
    isLocked = true;
}

void Bord::on_tblbord_doubleClicked(const QModelIndex &index)
{
    if(!isLocked)
        emit executeMove(index.column() + 1);
}

void Bord::on_tblbord_clicked(const QModelIndex &index)
{
    if(isLocked){
        QMessageBox msg;
        msg.setText("Neues Spiel erstellen!  Menü->Spiel->Neu");
        msg.exec();
    }
}
