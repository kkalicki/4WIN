#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#include <string>
#include "../h/sys/Konstanten.h"
#include "../h/net/msg/helloreply.h"

using namespace std;

enum GameMode {SVS,SVC,CVC};
enum NetworkMode {LOCAL,OPEN,JOIN};

class GameSettings{
public:
    GameSettings(GameMode mode=SVS,string player1Name="Player1",string player2Name="Player2",int bordId=4711,
                 unsigned short bordRows=Y,unsigned short bordColumns=X,unsigned short cellSize=CELL_SIZE,NetworkMode networkMode=LOCAL,int isFollow=false);
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

    int getIsFollow() const;
    void setIsFollow(int value);

    NetworkMode getNetworkMode() const;
    void setNetworkMode(const NetworkMode &value);

    string getRemoteIp() const;
    void setRemoteIp(const string &value);

private:
    GameMode mode;
    string player1Name;
    string player2Name;
    int bordId;
    unsigned short bordRows;
    unsigned short bordColumns;
    unsigned short cellSize;
    NetworkMode networkMode;
    int isFollow;
    string remoteIp;
};

#endif // GAMESETTINGS_H






