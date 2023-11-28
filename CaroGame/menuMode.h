#ifndef MENU_MODE_H
#define MENU_MODE_H

#include"Table.h"
#include"Bot.h"
#include"Player.h"
#include"inipp.h"
#include"IniFile.h"
#include<bits/stdc++.h>

void MainMenu(); // Main Menu with option to select
int selectMethod();
int chooseSize(); // Choose size of caro table
void Guild(); // How to play
void saveResultPvsP(int result); // Save result of Player vs Player mode
Player* setCurrentPlayer(PlayerManager* playerManager, Player *currentPlayer, string strPlayerName); // Set current player is playing
void printPlayerInfor(Player *currentPlayer); // Print information of player is playing
void printAllPlayerInfor(PlayerManager* playerManager);
void PvsP(Table &, string, string , PlayerManager*); // Player vs Player mode
int chooseModeBot();
void PvsBot(Table &, int); // Player vs Bot mode

#endif // TABLE_H
