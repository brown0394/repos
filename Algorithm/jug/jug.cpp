#include <iostream>
#include <fstream>
#define CASE 3
#define PASS 4
#define START 7

class Checkcase {
public:
    bool oppo_pass, mypass, needcase, both, either;
    Checkcase() :needcase(false), oppo_pass(false), mypass(false), both(false), either(false) {}
};

class CheckList {
    friend class Game;
    bool flag;
    Checkcase checkcase[4];
public:
    CheckList() : flag(false) {}
};

class Game {
    int _cases[CASE], _player, _loser;
    CheckList list[105];
public:
    Game(int case1 = 0, int case2 = 0, int case3 = 0) :_cases{ case1, case2, case3 },
        _player(1), _loser(0){list[0].flag = true; list[0].checkcase[3].needcase = true; list[0].checkcase[3].mypass = true; }

    void Play(int lastused, int stone, int level, bool pass1, bool pass2);
    char Winner();
    void LastReset();
};
void Game::LastReset() {
    _player = 1;
    _loser = 0;
}

void Game::Play(int lastused, int stone, int level, bool pass1, bool pass2) {
    bool lose = true;
    bool win = false;
    if (list[stone].flag) {
        for (int i = 0; i < 3; ++i) {
            if (list[stone].checkcase[i].needcase && lastused != i) {
                if (list[stone].checkcase[i].oppo_pass)
                {
                    if (level % 2 == 0)
                    {
                        if (!pass2)
                        {
                            win = true;
                        }
                    }
                    else if (level % 2 == 1)
                    {
                        if (!pass1)
                        {
                            win = true;
                        }
                    }
                    if (lastused != START && lastused != PASS)
                    {
                        int idx = stone + _cases[lastused];
                        list[idx].flag = true;
                        list[idx].checkcase[lastused].needcase = true;
                        list[idx].checkcase[lastused].mypass = true;
                    }
                    if(lastused == PASS && win){
                        list[stone].checkcase[3].needcase = false;
                        list[stone].checkcase[3].mypass = false;
                    }
                }
                else if (list[stone].checkcase[i].mypass)
                {
                    if (level % 2 == 0)
                    {
                        if (pass1)
                        {
                            win = true;
                        }
                    }
                    else if (level % 2 == 1)
                    {
                        if (pass2)
                        {
                            win = true;
                        }
                    }
                    if (lastused != START && lastused != PASS)
                    {
                        int idx = stone + _cases[lastused];
                        list[idx].flag = true;
                        list[idx].checkcase[lastused].needcase = true;
                        list[idx].checkcase[lastused].oppo_pass = true;
                    }
                    else if(lastused == PASS){
                        list[stone].flag = true;
                        list[stone].checkcase[3].needcase = true;
                        list[stone].checkcase[3].oppo_pass = true;
                    }
                }
                else
                {
                    win = true;
                    if (lastused != START && lastused != PASS)
                    {
                        list[stone + _cases[lastused]].checkcase[lastused].needcase = false;
                    }
                    else if(lastused == PASS){
                        list[stone].checkcase[3].needcase = false;
                    }
                    if (_loser == 0 && ((level % 2) == 0)) {
                        _loser = 1;
                    }
                    return;
                }
            }
        }
        if (list[stone].checkcase[3].needcase && lastused != PASS) {
            if (list[stone].checkcase[3].oppo_pass)
            {
                if (level % 2 == 0)
                {
                    if (!pass2)
                    {
                        win = true;
                    }
                }
                else if (level % 2 == 1)
                {
                    if (!pass1)
                    {
                        win = true;
                    }
                }
            }
            else if (list[stone].checkcase[3].mypass)
            {
                if (pass2 && ((level % 2) == 1))
                {
                    win = true;
                }
                else if (pass1 && ((level % 2) == 0))
                {
                    win = true;
                }
                if (lastused != START)
                {
                    int idx = stone + _cases[lastused];
                    list[idx].flag = true;
                    list[idx].checkcase[lastused].needcase = true;
                    list[idx].checkcase[lastused].oppo_pass = true;
                }
            }
        }
    }
    else {
        if (lastused != 0 && stone - _cases[0] >= 0) {
            Play(0, stone - _cases[0], level + 1, pass1, pass2);
            lose = false;
        }
        if (lastused != 1 && stone - _cases[1] >= 0) {
            Play(1, stone - _cases[1], level + 1, pass1, pass2);
            lose = false;
        }
        if (lastused != 2 && stone - _cases[2] >= 0) {
            Play(2, stone - _cases[2], level + 1, pass1, pass2);
            lose = false;
        }
        if (lastused != PASS) {
            if (pass2 && (level % 2 == 1)) {
                pass2 = false;
                Play(PASS, stone, level + 1, pass1, pass2);
                lose = false;
            }
            else if (pass1 && (level % 2 == 0)) {
                pass1 = false;
                Play(PASS, stone, level + 1, pass1, pass2);
                lose = false;
            }
        }
    }
    if (win) {
        if (_loser == 0 && ((level % 2) == 0)) {
            _loser = 1;
        }
    }
    else if (lose) {
        if (_loser == 0 && (level % 2)) {
            _loser = 1;
        }
        if (level == 1) {
            if (lastused == PASS) {
                list[stone].flag = true;
                list[stone].checkcase[3].needcase = true;
                list[stone].checkcase[3].mypass = true;
            }
            else if (!list[stone + _cases[lastused]].flag) {
                list[stone + _cases[lastused]].flag = true;
                list[stone + _cases[lastused]].checkcase[lastused].needcase = true;
            }
        }
    }
}


char Game::Winner() {
    if (_loser) {
        return 'F';
    }
    return 'S';
}

int main() {
    int choices[CASE];
    int stones;
    int last = 1;
    std::ifstream in("jug.inp");
    std::ofstream out("jug.out");

    for (int i = 0; i < CASE; ++i) {
        in >> choices[i];
    }
    Game game(choices[0], choices[1], choices[2]);
    for (int i = 0; i < 10; ++i) {
        in >> stones;
        if (last < stones) {
            ++last;
            for (; last < stones; ++last) {
                game.LastReset();
                game.Play(START, last, 0, true, true);
            }
        }
        game.LastReset();
        game.Play(START, stones, 0, true, true);
        out << game.Winner() << '\n';
        last = stones;
    }
    in.close();
    out.close();
}

