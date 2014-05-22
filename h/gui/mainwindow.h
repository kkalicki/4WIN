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
    void load4WinWidgets();
    void closeAllWidgets();
    ~MainWindow();

private slots:

    void on_actionBeenden_triggered();

    void on_actionNeu_triggered();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QWidget *settingsWidget;
    QWidget *bordWidget;
    QWidget *gameInfoWidget;
    static const int START_POSITION_X = 200;
    static const int START_POSITION_Y = 0;
};

#endif // MAINWINDOW_H
