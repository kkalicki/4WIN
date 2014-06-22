#include "../h/gui/gamesettings.h"

GameSettings::GameSettings(GameMode mode, string player1Name, string player2Name,
                           int bordId, unsigned short bordRows, unsigned short bordColumns,
                           unsigned short cellSize,NetworkMode networkMode, bool visitorMode)
{
    this->mode = mode;
    this->player1Name = player1Name;
    this->player2Name = player2Name;
    this->bordId = bordId;
    this->bordRows = bordRows;
    this->bordColumns = bordColumns;
    this->cellSize = cellSize;
    this->networkMode = networkMode;
    this->visitorMode = visitorMode;
    this->remoteIp = "";
}

GameSettings::~GameSettings()
{

}

GameMode GameSettings::getMode() const
{
return mode;
}

void GameSettings::setMode(const GameMode &value)
{
mode = value;
}
string GameSettings::getPlayer1Name() const
{
return player1Name;
}

void GameSettings::setPlayer1Name(const string &value)
{
player1Name = value;
}
string GameSettings::getPlayer2Name() const
{
return player2Name;
}

void GameSettings::setPlayer2Name(const string &value)
{
player2Name = value;
}
int GameSettings::getBordId() const
{
return bordId;
}

void GameSettings::setBordId(int value)
{
bordId = value;
}
unsigned short GameSettings::getBordRows() const
{
return bordRows;
}

void GameSettings::setBordRows(unsigned short value)
{
bordRows = value;
}
unsigned short GameSettings::getBordColumns() const
{
return bordColumns;
}

void GameSettings::setBordColumns(unsigned short value)
{
bordColumns = value;
}
unsigned short GameSettings::getCellSize() const
{
return cellSize;
}

void GameSettings::setCellSize(unsigned short value)
{
cellSize = value;
}

NetworkMode GameSettings::getNetworkMode() const
{
    return networkMode;
}

void GameSettings::setNetworkMode(const NetworkMode &value)
{
    networkMode = value;
}
string GameSettings::getRemoteIp() const
{
    return remoteIp;
}

void GameSettings::setRemoteIp(const string &value)
{
    remoteIp = value;
}
bool GameSettings::getVisitorMode() const
{
    return visitorMode;
}

void GameSettings::setVisitorMode(bool value)
{
    visitorMode = value;
}
int GameSettings::getGameId() const
{
    return gameId;
}

void GameSettings::setGameId(int value)
{
    gameId = value;
}



