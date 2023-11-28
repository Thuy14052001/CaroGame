#include"menuMode.h"

void MainMenu()
{
    cout << "*----------MAIN MENU----------*" << endl;
    cout << "1. Play with Other Player" << endl;
    cout << "2. Play with Bot" << endl;
    cout << "3. Player's Information" << endl;
    cout << "4. Guild" << endl;
    cout << "5. Exit" << endl << endl;
}

int selectMethod()
{
    int ans;
    do
    {
        cout << "Press number to select action: ";
        cin >> ans;
    } while (ans < 1 || ans > 5);
    return ans;
}

int chooseSize()
{
    int caro_size;
    do
    {
        cout << "Caro size (4 <= size <= 30): ";
        cin >> caro_size;
    } while (caro_size<4 || caro_size>30);
    return caro_size;
}

void Guild()
{
    cout << endl << "*------------How to play------------*" << endl;
    cout << "- Player enter move: row column" << endl;
    cout << "- If 1 player have 4 in a row, column of diagonal: win" << endl;
    cout << "- If all squares in table are checked and no player win: draw" << endl;
    cout << endl;
}

void saveResultPvsP(int res, string name2, string name1, PlayerManager* playerManager)
{
    if(res == 0)
    {
        cout << "Draw" << endl;
        for(int i=0;i<playerManager->m_vtPlayers.size(); i ++)
        {
            if(playerManager->m_vtPlayers[i]->GetName()==name1)
                playerManager->m_vtPlayers[i]->SetNumberOfDraw(playerManager->m_vtPlayers[i]->GetNumberOfDraw()+1);
            if(playerManager->m_vtPlayers[i]->GetName()==name2)
                playerManager->m_vtPlayers[i]->SetNumberOfDraw(playerManager->m_vtPlayers[i]->GetNumberOfDraw()+1);
        }
    }

    else if(res ==1)
    {
        cout << "Player " << name1 << " win" << endl;
        for(int i=0;i<playerManager->m_vtPlayers.size(); i ++)
        {
            if(playerManager->m_vtPlayers[i]->GetName()==name1)
                playerManager->m_vtPlayers[i]->SetNumberOfWin(playerManager->m_vtPlayers[i]->GetNumberOfWin()+1);
            if(playerManager->m_vtPlayers[i]->GetName()==name2)
               playerManager->m_vtPlayers[i]->SetNumberOfLoss(playerManager->m_vtPlayers[i]->GetNumberOfLoss()+1);
        }
    }

    else if(res==2)
    {
        cout << "Player " <<name2 << " win" << endl;
        for(int i=0;i<playerManager->m_vtPlayers.size(); i ++)
        {
            if(playerManager->m_vtPlayers[i]->GetName()==name2)
               playerManager->m_vtPlayers[i]->SetNumberOfWin(playerManager->m_vtPlayers[i]->GetNumberOfWin()+1);
            if(playerManager->m_vtPlayers[i]->GetName()==name1)
                playerManager->m_vtPlayers[i]->SetNumberOfLoss(playerManager->m_vtPlayers[i]->GetNumberOfLoss()+1);
        }
    }
}

Player* setCurrentPlayer(PlayerManager* playerManager, Player *currentPlayer, string strPlayerName)
{
    if (playerManager->FindIndexOfPlayer(strPlayerName) < 0)
	{
        cout << "Player is not existed. Program will create new player." << endl;
        currentPlayer->SetName(strPlayerName);
        currentPlayer->ClearWinLossDraw();
        playerManager->AddNewPlayer(strPlayerName);
        playerManager->SaveInformationToFile();
	}
	else // Player have been founded
	{
		currentPlayer = playerManager->GetInformationPlayer(strPlayerName);
	}
	return currentPlayer;
}

void printPlayerInfor(Player *currentPlayer)
{
    cout << "*------------- Player's information: -------------*" << endl;
	cout << "- Name: "<< currentPlayer->GetName() << endl;
	cout << "- Win: " << currentPlayer->GetNumberOfWin() << endl;
	cout << "- Draw: " << currentPlayer->GetNumberOfDraw() << endl;
	cout << "- Loss: " << currentPlayer->GetNumberOfLoss() << endl;
	cout << "*--------------------------------------------------*"<< endl << endl;

}

void printAllPlayerInfor(PlayerManager* playerManager)
{
    cout << setw(5) << left << "STT";
    cout << setw(30) << left << "Name";
    cout << setw(5) << left << "Win";
    cout << setw(5) << left << "Draw";
    cout << setw(5) << left << "Loss" << endl;
    cout << setw(70) << " " << endl;

    for(int i=0; i < playerManager->m_vtPlayers.size(); i ++)
    {
        cout << setw(5) << left << i+1;
        cout << setw(30) << left << playerManager->m_vtPlayers[i]->GetName();
        cout << setw(5) << left << playerManager->m_vtPlayers[i]->GetNumberOfWin();
        cout << setw(5) << left << playerManager->m_vtPlayers[i]->GetNumberOfDraw();
        cout << setw(5) << left << playerManager->m_vtPlayers[i]->GetNumberOfLoss() << endl;
    }
}

void PvsP(Table &caro, string name2, string name1, PlayerManager* playerManager)
{
    cout << "\nCaro table size " << caro.getTableSize() << " x " << caro.getTableSize() << endl;
    cout << name1 <<" - X   " << name2 << " - O" << endl;
    caro.DrawCaroTable();

    bool flag_player = false;
    while(true)
    {
        int res = caro.result();
        if(res != -1)
        {
            saveResultPvsP(res, name2, name1, playerManager);
            break;
        }

        int x, y;
        while(true)
        {
            string name;
            if(flag_player == false) name = name1;
            else name = name2;
            cout << "Player " << name << " move: ";
            cin >> x >> y;
            if(x<0 || x>=caro.getTableSize() || y<0 || y>=caro.getTableSize())
                cout << "Invalid value" << endl;
            else if(caro.getPlayer(x, y) != NP)
                cout << "Have been checked" << endl;
            else break;
        }
        caro.setPlayer(flag_player, x, y);
        cout << name1 <<" - X   " << name2 << " - O" << endl;
        caro.DrawCaroTable();
        flag_player = 1 - flag_player; // Player next
    }
}

int chooseModeBot()
{
    int mode;
    do
    {
        cout << "Mode of Bot: " << endl;
        cout << "1. Easy" << endl;
        cout << "2. Normal" << endl;
        cout << "3. Hard" << endl;
        cout << "Play with bot: ";
        cin >> mode;
    } while(mode!=1 && mode!=2 && mode!=3);
    return mode;
}

void PvsBot(Table &caro, int mode)
{
    cout << "\nCaro table size " << caro.getTableSize() << " x " << caro.getTableSize() << endl;
    cout << "Player 1 - X, Bot - O" << endl;
    caro.DrawCaroTable();

    Bot bot = Bot(mode);
    bool flag_player = false, first = true;
    int x, y;
    while(true)
    {
        int res = caro.result();
        if(res == 0) cout << "Draw" << endl;
        else if(res == 1)
        {
            caro.DrawCaroTable();
            cout << "Player win" << endl;
        }
        else if(res == 2) cout << "Bot win" << endl;
        if(res != -1)
            break;

        if(flag_player==false)
        {
            while(true)
            {
                cout << "Player move: ";
                cin >> x >> y;
                if(x<0 || x>=caro.getTableSize() || y<0 || y>=caro.getTableSize())
                    cout << "Invalid value" << endl;
                else if(caro.getPlayer(x, y) != NP)
                    cout << "Have been checked" << endl;
                else break;
            }
            caro.setPlayer(flag_player, x, y);
        }
        else
        {
            Move res;
            if (first==true)
            {
                res = bot.findBestMove(caro, x, y, first);
                first = false;
            }
            else res = bot.findBestMove(caro, x, y);
            caro.setPlayer(flag_player, res.row, res.col);
            cout << "\nPlayer 1 - X, Bot - O" << endl;
            caro.DrawCaroTable();
        }
        flag_player = 1 - flag_player; // Player next
    }
}
