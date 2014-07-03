#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include "ui_settings.h"
#include "../h/gui/gamesettings.h"
#include "../h/net/helloserver.h"
#include "../h/gui/threads/opengamesthread.h"

namespace Ui {
class settingsUi;

}
/**
 * @brief The Settings class
 * Klasse, die ein Fromular zum Eingeben der gewuenschten Einstellung repraesentiert
 */
class Settings : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief Settings Konstruktor
     * @param parent ParentWidget
     */
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    /**
     * @brief getGameMode Funktion, die den Spielmodus zurueckgibt
     * @return Spielmodus
     */
    GameMode getGameMode();

    /**
     * @brief getNetworkMode Funktion, die den Netzwerkmodus zurueckgibt
     * @return Netzwerkmodus
     */
    NetworkMode getNetworkMode();

    /**
     * @brief getLevel Funktion die den Schwierigkeitsgrad zurueckgibt
     * @return Schwierigkeitsgrad
     */
    Level getLevel();

    /**
     * @brief incomingGames Funktion, die aufgerufen wird, wenn ein RemoteSpiel antwortet, dass es offen ist
     * @param incomingVal Daten des Remotegames
     */
    void incomingGames(HelloReply incomingVal);

    /**
     * @brief start Funktion um dem Hauptfenster mittzuteilen, das es Im System, das Spiel je nach Einstellungen starten kann
     */
    void start();

private:
    Ui::settingsUi * ui;

    /**
     * @brief gameSettings Formulardaten werden in dieses Objekt gespeichert um dem System die Einstellungen mittzuteilen
     */
    GameSettings * gameSettings;

    /**
     * @brief openGameThread Thread, der die eingehenden offenen Spiele bearbeitet
     */
    OpenGameThread* openGameThread;
    QThread* guiThread;

    /**
     * @brief helloServer HelloServerObject, der Anfragenim Netzwerk taetigen kann um offene Spiele zu finden
     */
    HelloServer* helloServer;

    /**
     * @brief closeHelloServer Funktion um HelloServer zu schliessen
     */
    void closeHelloServer();

signals:
    /**
     * @brief resultSettings Signal, welches dem Hauptfenster signalisiert, dass Spiel begonnen werden kann
     * @param gameSettings
     */
    void resultSettings(GameSettings* gameSettings);

public slots:

private slots:
    /**
     * @brief on_rbsvs_toggled Funktion bei klick auf Radiobutton Spieler vs. Spieler
     * @param checked
     */
    void on_rbsvs_toggled(bool checked);

    /**
     * @brief on_rbsvc_toggled Funktion bei klick auf Radiobutton Spieler vs. Computer
     * @param checked
     */
    void on_rbsvc_toggled(bool checked);

    /**
     * @brief on_rbcvc_toggled Funktion bei klick auf Radiobutton Computer vs. Computer
     * @param checked
     */
    void on_rbcvc_toggled(bool checked);

    /**
     * @brief on_rblocal_toggled Funktion bei klick auf Radiobutton Lokale (Netzwerkspiel)
     * @param checked
     */
    void on_rblocal_toggled(bool checked);

    /**
     * @brief on_rbopen_toggled Funktion bei klick auf Radiobutton OPEN (Netzwerkspiel eroeffnen)
     * @param checked
     */
    void on_rbopen_toggled(bool checked);

    /**
     * @brief on_rbenter_toggled Funktion bei klick auf Radiobutton OPEN (Netzwerkspiel beitreten)
     * @param checked
     */
    void on_rbenter_toggled(bool checked);

    /**
     * @brief on_btnstart_clicked klick auf Button start
     */
    void on_btnstart_clicked();

    /**
     * @brief on_cbwatch_toggled Funktion, bei Checkbox aktivieren (Zuschauermodus)
     * @param checked
     */
    void on_cbwatch_toggled(bool checked);

    /**
     * @brief openGamesUpdate Funktion, um die Gui mit offenen Spielen zu aktualisieren
     * @param incomingVal
     */
    void openGamesUpdate(HelloReply *incomingVal);

    /**
     * @brief on_lvgames_itemActivated
     * @param item
     */
    void on_lvgames_itemActivated(QListWidgetItem *item);

    /**
     * @brief on_pbrefresh_clicked Funktion, um offene Spiele zu aktualisieren
     */
    void on_pbrefresh_clicked();

protected:
    /**
     * @brief closeEvent Funktion bei schließenb des Formulars
     * @param event
     */
    void closeEvent(QCloseEvent *event);
};

#endif // SETTINGS_H
