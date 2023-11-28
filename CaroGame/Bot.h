#ifndef BOT_H
#define BOT_H

#include<vector>
#include<ctime>
#include<cstdlib>
#include<math.h>
#include"Table.h"
using namespace std;

class Bot
{
private:
    int m_mode; // 1 - easy, 2 - normal, 3 - hard
public:
    Bot(int mode); // Constructor
    virtual ~Bot(); // Destructor
    vector<char> toList(Table &caro, int x, int y, int dx, int dy, int len = 3);
    int rowScore(vector<char> listInaRow, char player);
    void scoreOfListRow(Table &caro, vector<char> row, vector<int> &score, char player);
    int score(Table &caro, int x, int y, bool player, bool attack);
    int evaluate(Table &caro, int x, int y, bool player); // Score of a move
    Move findBestMove(Table &caro, int x, int y, bool first = false);
    Move easyMode(Table &caro, int x, int y);
    Move normalMode(Table &caro, int x, int y);
    Move hardMode(Table &caro, int x, int y, bool first = false);
};

#endif // BOT_H
