#include<iostream>
#include<vector>
#include<string>
#include<windows.h>
#include"Table.h"
#include"menuMode.h"
#include"Player.h"

using namespace std;

int main()
{
    int caro_size;
    MainMenu();

    PlayerManager* playerManager = new PlayerManager();
	Player *currentPlayer = new Player();

	// Check if already have playerManager file
	if (false == playerManager->ReadInformationFromFile()) { }

	// Set current player
	string strPlayerName;
	cout << "Please Input Name: ";
	cin >> strPlayerName;
	currentPlayer = setCurrentPlayer(playerManager, currentPlayer, strPlayerName);
	printPlayerInfor(currentPlayer); // Print current player information

    while(true)
    {
        int ans = selectMethod();
        if(ans == 5) break;
        switch(ans)
        {
        case 1:
            {
                Player *currentPlayer2 = new Player();
                string strPlayer2Name;
                while(true)
                {
                    cout << "Please Input Name: ";
                    cin >> strPlayer2Name;
                    if(strPlayer2Name == currentPlayer->GetName()) // If player2's name the same as player1's name
                        cout<< "Enter a different player" << endl;
                    else break;
                }

                currentPlayer2 = setCurrentPlayer(playerManager, currentPlayer2, strPlayer2Name);
                printPlayerInfor(currentPlayer2);

                caro_size = chooseSize();
                Table caro(caro_size);
                PvsP(caro, currentPlayer2->GetName(), currentPlayer->GetName(), playerManager);
                playerManager->SaveInformationToFile();
                break;
            }
        case 2:
            {
                caro_size = chooseSize();
                int mode = chooseModeBot();
                Table caro(caro_size);
                PvsBot(caro, mode);
                break;
            }
        case 3:
            {
                printAllPlayerInfor(playerManager);
                break;
            }
        case 4:
            {
                Guild();
                break;
            }
        default:
            break;
        }
        cout << endl << "*--------- Back to main menu ---------*" << endl << endl;
        MainMenu();
    }

    delete playerManager;
    return 0;
}
