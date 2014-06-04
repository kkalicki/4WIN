#include "../h/gui/history.h"
#include "../h/gui/historyitem.h"
#include <QStandardItemModel>
#include <sstream>

History::History(QWidget *parent)  : QWidget(parent),
    ui(new Ui::historyUi)
{
    ui->setupUi(this);
    init();
}

History::~History()
{
    //delete model;
    delete ui;
}


void History::init()
{
    this->move(START_POSITION_X,START_POSITION_Y);
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint);
    this->setFixedSize(this->size().width(),this->size().height());
    //this->model = new QStandardItemModel();
    //ui->lvhistorie->setModel(model);
}

void History::preExecute()
{
   clear();
}


void History::postExecute()
{
    //keine implementierung notwendig...
}

void History::addHisItem(HisEintrag * addItem)
{
    ostringstream o;
    o << addItem->getRunde()<< ") " << addItem->getSpieler()->getName() << " : " << addItem->getZeile() << " - " << addItem->getSpalte();
    //QStandardItem * newItem = new QStandardItem(QString::fromStdString(o.str()));

    //model->appendRow(newItem);
    //ui->lvhistorie->scrollToBottom();
   //HistoryItem* hisItem = new HistoryItem(addItem);
    QListWidgetItem *item = new QListWidgetItem();
    item->setText(QString::fromStdString(o.str()));
    ui->lsthistory->addItem(item);
    //ui->lsthistory->setItemWidget(item, hisItem );
    ui->lsthistory->scrollToBottom();
}

void History::clear()
{
    //model->clear();
    ui->lsthistory->clear();
}
