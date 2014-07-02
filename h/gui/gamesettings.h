#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/net/msg/helloreply.h"

using namespace std;

enum GameMode {SVS,SVC,CVC};
enum NetworkMode {LOCAL,OPEN,JOIN};
enum Level {EASY=0,MEDIUM=3,HARD=6,ULTIMATE=9};

class GameSettings{
public:
    GameSettings(GameMode mode=SVS,Level level=MEDIUM, string player1Name="Player1", string player2Name="Player2", int bordId=4711,
                 unsigned short bordRows=Y, unsigned short bordColumns=X, unsigned short cellSize=CELL_SIZE, NetworkMode networkMode=LOCAL, bool visitorMode=false);
    ~GameSettings();

    GameMode getMode() const;
    void setMode(const GameMode &value);

    string getPlayer1Name() const;
    void setPlayer1Name(const string &value);

    string getPlayer2Name() const;
    void setPlayer2Name(const string &value);

    int getBordId() const;
    void setBordId(int value);

    unsigned short getBordRows() const;
    void setBordRows(unsigned short value);

    unsigned short getBordColumns() const;
    void setBordColumns(unsigned short value);

    unsigned short getCellSize() const;
    void setCellSize(unsigned short value);

    NetworkMode getNetworkMode() const;
    void setNetworkMode(const NetworkMode &value);

    string getRemoteIp() const;
    void setRemoteIp(const string &value);

    bool getVisitorMode() const;
    void setVisitorMode(bool value);

    int getGameId() const;
    void setGameId(int value);

    Level getLevel() const;
    void setLevel(const Level &value);

private:
    GameMode mode;
    Level level;
    string player1Name;
    string player2Name;
    int bordId;
    unsigned short bordRows;
    unsigned short bordColumns;
    unsigned short cellSize;
    NetworkMode networkMode;
    int gameId;
    bool visitorMode;
    string remoteIp;
};

#endif // GAMESETTINGS_H






