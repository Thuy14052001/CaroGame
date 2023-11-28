#include "Player.h"

Player::Player()
{
	m_strName = "";
	m_nNumberOfWin = 0;
	m_nNumberOfLoss = 0;
	m_nNumberOfDraw = 0;
}

string Player::GetName()
{
    return m_strName;
}
void Player::SetName(string name)
{
    m_strName = name;
}

int Player::GetNumberOfWin()
{
    return m_nNumberOfWin;
}
void Player::SetNumberOfWin(int nNumberOfWin)
{
	m_nNumberOfWin = nNumberOfWin;
}

int Player::GetNumberOfLoss()
{
    return m_nNumberOfLoss;
}
void Player::SetNumberOfLoss(int nNumberOfLoss)
{
	m_nNumberOfLoss = nNumberOfLoss;
}

int Player::GetNumberOfDraw()
{
    return m_nNumberOfDraw;
}
void Player::SetNumberOfDraw(int nNumberOfDraw)
{
	m_nNumberOfDraw = nNumberOfDraw;
}

void Player::IncreaseWin()
{
    m_nNumberOfWin++;
}
void Player::IncreaseLoss()
{
    m_nNumberOfLoss++;
}
void Player::IncreaseDraw()
{
    m_nNumberOfDraw++;
}
void Player::ClearWinLossDraw()
{
    m_nNumberOfDraw = 0;
    m_nNumberOfWin = 0;
    m_nNumberOfLoss = 0;
}

PlayerManager::PlayerManager()
    :m_iniFile("","")
{
    char strPath[256];
    getcwd(strPath, 255);
	string strFileDir(strPath); // convert to string.
    string strFileName = "PlayerManager.ini";
    m_iniFile = IniFile(strFileDir, strFileName);
}


int PlayerManager::SaveInformationToFile()
{
    const string strPlayerList = "PLAYER_LIST";
    m_iniFile.WriteStringValue(strPlayerList, "PlayerCount",  to_string(m_vtPlayers.size()));

	// Luu Danh sach ten nguoi choi
    for(int i = 0; i < m_vtPlayers.size(); i ++)
    {
        string strName = m_vtPlayers[i]->GetName();
        m_iniFile.WriteStringValue(strPlayerList, to_string(i), strName);
    }

	// Luu Nguoi choi
    for(int i = 0; i < m_vtPlayers.size(); i ++)
    {
		string strName = m_vtPlayers[i]->GetName();
		m_iniFile.WriteStringValue(strName, "Win", to_string(m_vtPlayers[i]->GetNumberOfWin()));
		m_iniFile.WriteStringValue(strName, "Draw", to_string(m_vtPlayers[i]->GetNumberOfDraw()));
		m_iniFile.WriteStringValue(strName, "Loss", to_string(m_vtPlayers[i]->GetNumberOfLoss()));
    }

	return 1;
}

int PlayerManager::ReadInformationFromFile()
{
    vector<string> vtPlayerName;
    const string strPlayerList = "PLAYER_LIST";
    int nPlayerCount = m_iniFile.ReadIntValue(strPlayerList, "PlayerCount", 0); // Lay tong so nguoi choi de chay vong lap

    // Lay Ten cac player
	for (int i = 0; i < nPlayerCount; i++)
	{
		string strName = m_iniFile.ReadStringValue(strPlayerList, to_string(i), "PlayerName");
		vtPlayerName.push_back(strName);
	}

    // Lay Thong Tin Cac Player
	m_vtPlayers.clear();
	for (int i = 0; i < nPlayerCount; i++)
	{
		Player* player = new Player();
		string strName = vtPlayerName[i];
		player->SetName(vtPlayerName[i]);

		int nNumberOfWin = m_iniFile.ReadIntValue(strName, "Win", 0);
		player->SetNumberOfWin(nNumberOfWin);

		int nNumberOfDraw = m_iniFile.ReadIntValue(strName, "Draw", 0);
		player->SetNumberOfDraw(nNumberOfDraw);

		int nNumberOfLoss = m_iniFile.ReadIntValue(strName, "Loss", 0);
		player->SetNumberOfLoss(nNumberOfLoss);

		m_vtPlayers.push_back(player);
	}

	return 1;
}

Player* PlayerManager::GetInformationPlayer(string strName)
{
    // Duyet danh sach kiem tra xem co strName
    int nIndex = FindIndexOfPlayer(strName);

    // Neu' co' -> tra ve 1 phan tu trong vector player
    if(nIndex >= 0)
    {
        return m_vtPlayers.at(nIndex);
    }

    // Neu' ko co -> return null
    // return std::nullptr_t;
}

// Tra ve Index cua Player co ID = strName
// Neu gia tri tra ve -1 ==> Ko Ton tai Player voi strInputID
// Neu Ton tai, tra ve Index trong m_vtPlayer
int PlayerManager::FindIndexOfPlayer(string strName)
{
    for(int i = 0; i < m_vtPlayers.size(); i++)
    {
        string strPlayerName = m_vtPlayers[i]->GetName();
        if(strName == strPlayerName)
        {
            return i;
        }
    }

    return -1;
}

bool PlayerManager::AddNewPlayer(string strName)
{
	// Kiem Tra Nguoi Choi Da Ton Tai hay chua
	if (FindIndexOfPlayer(strName) >= 0) // Nguoi choi da ton tai
	{
		return false;
	}

	// Tao moi nguoi dung
	Player* player = new Player();
	player->SetName(strName);

	// Luu nguoi dung vao vector
	m_vtPlayers.push_back(player);
}



