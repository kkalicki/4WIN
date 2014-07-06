#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <../4WIN/h/gui/I4WinWidget.h>
#include <../4WIN/h/gui/threads/movethread.h>
#include <../4WIN/h/gui/threads/giveupthread.h>
#include <../4WIN/h/gui/threads/visitorthread.h>
#include <../4WIN/h/net/msg/visitorpackage.h>
#include <../h/gui/bord.h>
#include <../h/gui/settings.h>
#include <../h/gui/gameinfo.h>
#include <../h/gui/gamesettings.h>
#include <../h/gui/history.h>
#include <../h/sys/spiel.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 * Klasse, die das Hauptfenster repraesentiert. In dieses Widget wird das GameInfoWidget geladen und dient als Zugangspunkt zum System
 */
class MainWindow : public QMainWindow, public I4WinWidget
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow Konstruktor
     * @param parent ParentWidget
     */
    explicit MainWindow(QWidget *parent = 0);

    /**
     * @brief load4WinWidgets Funktion, die alle 4WinWidgets laed
     */
    void load4WinWidgets();

    /**
     * @brief closeAllWidgets Funktion, die alle 4WinWidgets schliesst
     */
    void closeAllWidgets();

    /**
     * @brief killNetworkSignalSlot Funktion, die alle Signale von den verwendeten Funktionen trennt
     */
    void killNetworkSignalSlot();

    /**
     * @brief killNetworkSignalSlot Funktion, die alle Signale an die entsprechenden Funktionen bindet
     */
    void initNetworkSignalSlot();

    /**
     * @brief lockBoad Funktion die das Spielfeld laed
     */
    void lockBoad();

    /**
     * @brief init Funktion, welche zum Initilisieren des Widgets erforderlich ist. Vererbung durch Interface
     */
    virtual void init();

    /**
     * @brief preExecute Funktion, welche ausgefueht wird bevor das Spiel beginnt. Vererbung durch Interface
     */
    virtual void preExecute();

    /**
     * @brief postExecute Funktion, welche ausgefueht wird nachdem ein Spiel beendet wurde, Vererbung durch Interface
     */
    virtual void postExecute();

    /**
     * @brief showException Funktion, die Fehlermeldungen aus dem System anzeigt
     * @param e
     */
    void showException(exception &e);
    ~MainWindow();

private slots:
    /**
     * @brief on_endGame Funktion, die zu Spielende aufgerufen wird
     * @param winner Klasse Spieler, der Gewonnen hat
     * @param giveUp Flag, ob aufgegeben wurde
     */
    void on_endGame(Spieler* winner, bool giveUp);

    /**
     * @brief on_exitVisitorMode Funktion, um den Visitormodus zu verlassen
     */
    void on_exitVisitorMode();

    /**
     * @brief on_executeMove Funktion, um einen Zug auszufueheren
     * @param column Spalte in die geworfen werden soll
     */
    void on_executeMove(unsigned short column);

    /**
     * @brief on_resultSettings Funktion, die die Einstellungen auswertet und das Sysetm je nach Einstellung initialisiert
     * @param gameSettings GameSettingsObjekt
     */
    void on_resultSettings(GameSettings* gameSettings);

    /**
     * @brief on_actionBeenden_triggered Funktion, die nach Klicken auf den Button Beenden im Menue aufgerufen wird
     */
    void on_actionBeenden_triggered();

    /**
     * @brief on_actionNeu_triggered Funktion, die aufgerufen wird, wenn ein neues Spiel erstellt werden soll Menue-->Neu
     */
    void on_actionNeu_triggered();

    /**
     * @brief update Funktion, um die GUI zu aktualisieren
     * @param column Spalte die aktualisiert werden soll
     * @param result Falg fuer Gewonnen/Unentschieden oder Aufgegeben
     */
    void update(unsigned short column, int result);

    /**
     * @brief startGame Funktion um der Gui mitzuteilen,dass ein Spiel beginnt
     */
    void startGame();

    /**
     * @brief stopMoveThread Funktion um den MoveThread fuer die aktualisierung nach jedem Zug beendet
     */
    void stopMoveThread();

    /**
     * @brief stopMoveThread Funktion um den GiveUpThread nach dem Aufgeben eines Remotespielers beendet
     */
    void stopGiveUpThread();

    void stopVpThread();

    /**
     * @brief incommingMove Funktion, um einen Zug aus dem System zu taetigen. KISpieler, RemoteSpieler
     * @param column Spalte in die geworfen wird
     * @param row Zeile in die geworfen wird
     */
    void incommingMove(unsigned short column, int row);

    /**
     * @brief incommingVp Funktion, um ein VisitorPackage zu bearbeiten und in der GUI anzuzeigen (VisitorMode)
     * @param vp            VisitorPackage enthaelt die Informationen um die Zuege durchzufuehren
     * @param lastround     Letzte Runde, um mit der lokalen letzten Runde zu vergleichen
     */
    void incommingVp(VisitorPackage vp, int lastround);

    /**
     * @brief incommingGiveUp Funktion, die aufgerufen wird, wenn ein Spieler aufgibt (Netzwerkspiel)
     * @param remoteSpieler  RemoteSpieler
     * @param giveUp         Flag ob Aufgegeben wurde
     */
    void incommingGiveUp(Spieler* remoteSpieler, bool giveUp);

protected:
    /**
     * @brief closeEvent Funktion, die aufgerufen wird, wenn das Hauptfenster geschlossen wird
     * @param event WindowEvents
     */
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;

    /**
     * @brief settingsWidget Widget zur Anzeige der Einstellungen
     */
    Settings *settingsWidget;

    /**
     * @brief bordWidget Widget, fuer das Spielfeld
     */
    Bord *bordWidget;

    /**
     * @brief gameInfoWidget Widget, fuer die Spielinformationen
     */
    GameInfo *gameInfoWidget;

    /**
     * @brief historyWidget Widget fuer die Historieeintraege
     */
    History * historyWidget;

    /**
     * @brief gameSettings Einstellungen des aktuellen Spiels
     */
    GameSettings * gameSettings;

    /**
     * @brief guiUpdaterThread Thread zum Updaten der Gui nach jedem Zug
     */
    MoveThread *guiUpdaterThread;

    /**
     * @brief giveUpThread Thread, der der GUI mitteilt, wenn ein Spieler aufgibt
     */
    GiveUpThread *giveUpThread;

    /**
     * @brief visitorThread Thread der die Informationen fuer den Zuschauermodus verarbeitet
     */
    VisitorThread *visitorThread;

    QThread * guiMoveThread;
    QThread * guiGiveUpThread;
    QThread * guiVpThread;

    /**
     * @brief START_POSITION_X Konstante fuer Startposition auf dem Bildschirm (X-Position)
     */
    static const int START_POSITION_X = 230;

    /**
     * @brief START_POSITION_Y Konstante fuer Startposition auf dem Bildschirm (Y-Position)
     */
    static const int START_POSITION_Y = 0;

    Spiel *game;
};

#endif // MAINWINDOW_H
