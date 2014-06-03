#ifndef GUIUPDATER_H
#define GUIUPDATER_H

#include   <QObject>
class GuiUpdater : public QObject
{
   Q_OBJECT

public:
    GuiUpdater(unsigned short column, int row);
public slots:
    void process();
signals:
    void updateGui(unsigned short column, int row);

private:
    unsigned short column;
    int row;
};
#endif // GUIUPDATER_H
