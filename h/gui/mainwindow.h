#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void loadSettingWidget();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *settingsWidget;
    QWidget *bordWidget;
};

#endif // MAINWINDOW_H
