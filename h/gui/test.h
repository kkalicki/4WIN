#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include "ui_test.h"

namespace Ui {
class testUi;
}

class Test : public QWidget
{
    Q_OBJECT
public:
    explicit Test(QWidget * parent=0);
    ~Test();
private slots:
    void on_pushButton_clicked();

private:
     Ui::testUi *ui;
};

#endif // TEST_H
