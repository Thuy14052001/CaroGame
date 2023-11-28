#include "Bot.h"

Bot::Bot(int mode): m_mode(mode) { }

Bot::~Bot() { }

vector<char> Bot::toList(Table &caro, int x, int y, int dx, int dy, int len)
{
    // dx, dy: huong di (0, 1):-, (1, 0):|, (1, 1): \, (-1, 1): /
    int caro_size = caro.getTableSize();
    vector<char> res;
    for(int i=-len; i<=len; i++)
    {
        if(x+i*dx >= 0 && x+i*dx<caro_size && y+i*dy >= 0 && y+i*dy<caro_size)
            res.push_back(caro.getPlayer(x+i*dx, y+i*dy));
    }
    return res;
}

int Bot::rowScore(vector<char> listInaRow, char player)
{
    int blank = 0, filled = 0;
    for(auto c: listInaRow)
    {
        if(c == NP) blank++;
        if(c == player) filled++;
    }
    if(blank+filled <4) return 0;
    else return filled;
}

void Bot::scoreOfListRow(Table &caro, vector<char> row, vector<int> &score, char player)
{
    if(row.size()<4) return;
    for(int i=0; i<row.size()-3; i++)
    {
        vector<char> sublist(row.begin()+i, row.begin()+i+4);
        int s = rowScore(sublist, player);
        score[s]++;
    }
}

int Bot::score(Table &caro, int x, int y, bool player, bool attack)
{
    int M;
    if(attack == true) M = 1000; // multiplier for attack score
    else M = 400; // multiplier for defense score
    caro.setPlayer(player, x, y);
    vector<int> list_score(5, 0);
    vector<pair<int, int>> dir{make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(-1,1)};
    for(auto d: dir)
    {
        vector<char> row = toList(caro, x, y, d.first, d.second);
        scoreOfListRow(caro, row, list_score, caro.getPlayer(x, y));
    }
    caro.resetPlayer(x, y); // Undo the move
    int sum_score = list_score[0] + list_score[1] + 8*list_score[2] + 32*list_score[3] + M*list_score[4];
    return sum_score;
}

int Bot::evaluate(Table &caro, int x, int y, bool player)
{
    int act_score = score(caro, x, y, player, true);
    int def_score = score(caro, x, y, !player, false);

    int sum_score = act_score + def_score;
    return sum_score;
}

Move Bot::findBestMove(Table &caro, int x, int y, bool first)
{
    if(m_mode == 1) return easyMode(caro, x, y);
    else if(m_mode == 2) return normalMode(caro, x, y);
    else if(m_mode == 3) return hardMode(caro, x, y, first);
}

Move Bot::easyMode(Table &caro, int x, int y)
{
    srand(time(0));
    vector<Move> r = caro.findPosibleMove();
    int index = rand() % r.size();
    return r.at(index);
}

Move Bot::normalMode(Table &caro, int x, int y)
{
    srand(time(0));
    vector<Move> r = caro.findPosibleMove(x, y);
    int index = rand() % r.size();
    return r.at(index);
}

Move Bot::hardMode(Table &caro, int x, int y, bool first)
{
    if(first == true) return normalMode(caro, x, y);
    int bestVal = -100000;
    Move bestMove;
	vector<Move> psbl_move = caro.findPosibleMove();

	for(auto p: psbl_move)
    {
        int i = p.row, j = p.col;
        int moveVal = evaluate(caro, i, j, true); // compute evaluation function for this move.
        if (moveVal > bestVal) // update best
        {
            bestMove.setMove(i, j);
            bestVal = moveVal;
        }
    }
	return bestMove;
}
