#ifndef I4WINWIDGET_H
#define I4WINWIDGET_H

/**
 * @brief The I4WinWidget class
 * Klasse die ein 4WinWidget definiert. Diese Klasse enthaelt nur Rein Virtuelle Funktionen
 */
class I4WinWidget{
public:
    /**
     * @brief init Funktion, um ein 4WinWidget zu initalisieren
     */
    virtual void init()=0;

    /**
     * @brief preExecute Funktion, die jedes 4WinWidget zu beginn eines Spiels ausfuehrt
     */
    virtual void preExecute()=0;

    /**
     * @brief postExecute Funktion, die jedes 4WinWidget nach beenden eines Spiels ausfuehrt
     */
    virtual void postExecute()=0;

    /**
     * @brief getIsActiveGame Getter, ob Spiel akiv ist
     * @return true/false
     */
    bool getIsActiveGame() const{
        return isActiveGame;
    }

    /**
     * @brief setIsActiveGame Setter, ob ein Spiel aktiv ist
     * @param value Wert
     */
    void setIsActiveGame(bool value){
        isActiveGame = value;
    }

private:
    /**
     * @brief isActiveGame Falg, ob Spiel aktiv ist
     */
    bool isActiveGame=0;
};

#endif // I4WINWIDGET_H

