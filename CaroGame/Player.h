#ifndef PLAYER_H
#define PLAYER_H

#include<iostream>
#include<vector>
#include "IniFile.h"
#include <windows.h>
#include <winnt.h>
#include <unistd.h>
#include <string.h>

using namespace std;

class Player
{
public:
    Player();

private:
    string m_strName;
    int m_nNumberOfWin;
    int m_nNumberOfLoss;
    int m_nNumberOfDraw;

public:
    string GetName();
    void SetName(string name);
    int GetNumberOfWin();
	void SetNumberOfWin(int nNumberOfWin);
    int GetNumberOfLoss();
	void SetNumberOfLoss(int nNumberOfLoss);
    int GetNumberOfDraw();
	void SetNumberOfDraw(int nNumberOfDraw);
    void IncreaseWin();
    void IncreaseLoss();
    void IncreaseDraw();
    void ClearWinLossDraw();
};

class PlayerManager
{
private:
    IniFile m_iniFile;
public:
    PlayerManager();
    vector<Player*> m_vtPlayers;
    int SaveInformationToFile();
    int ReadInformationFromFile();

    Player* GetInformationPlayer(string strName);
    int FindIndexOfPlayer(string strName);

	bool AddNewPlayer(string strName);
};

#endif // PLAYER_H


