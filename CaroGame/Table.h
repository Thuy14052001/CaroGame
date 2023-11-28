#ifndef TABLE_H
#define TABLE_H

#include<iostream>
#include<vector>
#include<cstdlib>
using namespace std;

#define P1 'X' // Player 1
#define P2 'O' // Player 2
#define NP ' ' // No player

struct Move
{
    int row, col;
    Move(int x = -1, int y = -1): row(x), col(y) {}
    void setMove(int x, int y){row = x; col = y;}
};

class Table
{
private:
    int m_table_size;
    char **m_playermove;
public:
    Table(int table_size = 10); // Constructor
    ~Table(); // Destructor
    const int getTableSize(); // Return size of table
    const char getPlayer(int x, int y); // Return player at position (x, y)
    void DrawCaroTable(); // Draw table
    void setPlayer(bool player, int x, int y); // Set player at position (x, y)
    void resetPlayer(int x, int y);
    bool isCheckedAll(); // If all squares in caro table is checked
    int winningCondition(); // If 1 of 2 player win/ lose/ draw
    int result(); // Result of caro table
    vector<Move> findPosibleMove(int x=-1, int y=-1); // Find all move around position (x, y) or move that haven't been checked
    vector<Move> findCloseMove(); // Find move that in squares size 3x3 around have move have been checked
};

#endif // TABLE_H
