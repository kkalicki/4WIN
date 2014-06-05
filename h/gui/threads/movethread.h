#ifndef GUIUPDATER_H
#define GUIUPDATER_H

#include   <QObject>
class MoveThread : public QObject
{
   Q_OBJECT

public:
    MoveThread(unsigned short column, int row);
public slots:
    void process();
signals:
    void updateGui(unsigned short column, int row);

private:
    unsigned short column;
    int row;
};
#endif // GUIUPDATER_H
