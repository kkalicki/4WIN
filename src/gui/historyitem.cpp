
#include "../h/gui/historyitem.h"
#include "../h/sys/Konstanten.h"

HistoryItem::HistoryItem(HisEintrag *item, QWidget *parent): QWidget(parent),
    ui(new Ui::historyItemUi)
{
    ui->setupUi(this);
    //this->setFixedSize(this->size().width(),33);
    //this->setSizePolicy(QLayout::SetFixedSize);
    //this->sesetSizeConstraint( QLayout::SetFixedSize );
    this->hisEintrag = item;

    if(item->getSpieler()->getFarbe() == ROT){
        //load redImage...
        this->image = new QPixmap(":/image/red_point.png");
    }
    else{
        this->image = new QPixmap(":/image/yellow_point.png");
    }
    initControls();
}

HistoryItem::~HistoryItem()
{
    delete image;
    delete ui;
}

void HistoryItem::initControls()
{
    this->ui->lblround->setText(QString::number(hisEintrag->getRunde()));
}
