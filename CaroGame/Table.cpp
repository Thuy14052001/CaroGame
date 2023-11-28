#include "Table.h"

Table::Table(int table_size): m_table_size(table_size)
{
    m_playermove = new char*[table_size];
    for(int i=0; i<table_size; i++)
        m_playermove[i] = new char[table_size];
    for(int i=0; i< table_size; i++)
        for(int j=0; j<table_size; j++)
            m_playermove[i][j] = NP;
}

Table::~Table()
{
    for(int i=0; i<m_table_size; i++) delete[] m_playermove[i];
    delete[] m_playermove;
}

const int Table::getTableSize() // Return size of table
{
    return m_table_size;
}

const char Table::getPlayer(int x, int y) // Return player at position (x, y)
{
    return m_playermove[x][y];
}

void Table::DrawCaroTable() // Draw table
{
    // Draw table
    cout << " ";
    for(int j=0; j<m_table_size; j++)
    {
        if (j < 10) cout << "   " << j;
        else cout << "  " << j;
    }
    cout << endl;
    for(int i=0; i<=m_table_size; i++)
    {
        cout << "  ";
        for(int j=0; j<m_table_size; j++) cout << "|---";
        cout << "|" << endl;
        if(i==m_table_size) break;
        if(i<10) cout << i << " ";
        else cout << i;
        for(int j=0; j<m_table_size; j++)
            cout << "| " << getPlayer(i, j) << " ";
        cout << "|" << endl;
    }
    cout << endl;
}

void Table::setPlayer(bool player, int x, int y) // Set player at position (x, y)
{
    if(player==false) m_playermove[x][y] = P1;
    else if(player==true) m_playermove[x][y] = P2;
}

void Table::resetPlayer(int x, int y)
{
    m_playermove[x][y] = NP;
}

bool Table::isCheckedAll() // If all squares in caro table is checked
{
    for(int i=0; i<m_table_size; i++)
        for(int j=0; j< m_table_size; j++)
            if(getPlayer(i, j) == NP)
                return false;
    return true;
}

int Table::winningCondition() // If player win/ lose/ draw
{
    // Row win
    for(int i=0; i<m_table_size; i++)
    {
        int count_player = 1;
        for (int j = 0; j<m_table_size-1; j++)
        {
            if(getPlayer(i, j) != NP && getPlayer(i, j) == getPlayer(i, j+1))
                count_player++;
            else count_player = 1;
            if(count_player == 4)
            {
                if(getPlayer(i, j) == P1) return 1;
                else if(getPlayer(i, j) == P2) return 2;
            }
        }
    }

    // Column win
    for(int i=0; i<m_table_size; i++)
    {
        int count_player = 1;
        for (int j = 0; j<m_table_size-1; j++)
        {
            if(getPlayer(j, i) != NP && getPlayer(j, i) == getPlayer(j+1, i))
                count_player++;
            else count_player = 1;
            if(count_player == 4)
            {
                if(getPlayer(j, i) == P1) return 1;
                else if(getPlayer(j, i) == P2) return 2;
            }
        }
    }

    // Diagonal \ win
    for(int i=0; i< m_table_size-3; i++)
    {
        for(int j = 0; j< m_table_size-3-i; j++)
        {
            if(i!=0 && j!=0) continue;
            int count_player = 1;
            int p = m_table_size - (i+j);
            for(int k = 0; k<p-1; k++)
            {
                if(getPlayer(i+k, j+k) != NP && getPlayer(i+k, j+k) == getPlayer(i+k+1, j+k+1))
                    count_player++;
                else count_player = 1;
                if(count_player == 4)
                {
                    if(getPlayer(i+k, j+k) == P1) return 1;
                    else if(getPlayer(i+k, j+k) == P2) return 2;
                }
            }
        }
    }

    // Diagonal / win
    for(int i = m_table_size-1; i >= 3; i--)
    {
        for(int j = 0; j < i-3+1; j++)
        {
            if(i != m_table_size-1 && j != 0) continue;
            int count_player = 1;
            int p = abs(i-j) + 1;
            for(int k = 0; k<p-1; k++)
            {
                if(getPlayer(i-k, j+k) != NP && getPlayer(i-k, j+k) == getPlayer(i-k-1, j+k+1))
                    count_player++;
                else count_player = 1;
                if(count_player == 4)
                {
                    if(getPlayer(i-k, j+k) == P1) return 1;
                    else if(getPlayer(i-k, j+k) == P2) return 2;
                }
            }
        }
    }

    return 0;
}

int Table::result() // Result of caro table
{
    if (isCheckedAll() == true) return 0; // Full --> Draw
    int win = winningCondition();
    if (win != 0) return win;
    return -1; // No result yet, game continue
}

vector<Move> Table::findPosibleMove(int x, int y) // Find all move around position (x, y) or move that haven't been checked
{
    vector<Move> res;
    if(x==-1 && y==-1) // If x=y=-1 -> find move that haven't been checked
    {
        for (int i = 0; i<m_table_size; i++)
            for (int j = 0; j<m_table_size; j++)
                if (getPlayer(i, j)==NP) res.push_back(Move(i, j));
    }

    else // Find all move around position (x, y)
    {
        int pos = 1;
        while(res.size() == 0)
        {
            for(int i=-pos; i<=pos; i++)
            {
                if(x+i >= m_table_size || x+i<0) continue;
                for(int j=-pos; j<=pos; j++)
                {
                    if(i==0 && j==0) continue;
                    if(y+j >= m_table_size || y+j<0) continue;
                    if(getPlayer(x+i, y+j) == NP)
                        res.push_back(Move(x+i, y+j));
                }
            }
            pos++;
        }
    }

    return res;
}

vector<Move> Table::findCloseMove() // Find move that in squares size 3x3 around have move that have been checked
{
    vector<Move> res;
    vector<Move> posMove = findPosibleMove();
    for(auto p:posMove)
    {
        int i = p.row, j = p.col;
        vector<Move> subvec = findPosibleMove(i, j);
        if(subvec.size()>0) res.push_back(Move(i, j));
    }
    return res;
}
