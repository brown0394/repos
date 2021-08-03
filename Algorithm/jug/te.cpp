#include <iostream>
#include <fstream>
#define CASE 3
#define PASS 4
#define START 7

class Checkcase {
public:
    bool needcase;
    Checkcase() :needcase(false) {}
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
        _player(1), _loser(0){list[0].flag = true; list[0].checkcase[3].needcase = true; }

    void Play(int lastused, int stone, int level, bool pass1, bool pass2);
    char Winner();
    void LastReset();
    void test();
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
                win = true;
            }
        }
        if (list[stone].checkcase[3].needcase && lastused != PASS) {
            win = true;
        }
    }
    else {
        if (lastused != 0 && stone - _cases[0] >= 0) {
            _player = 0;
            Play(0, stone - _cases[0], level + 1, pass1, pass2);
            lose = false;
            if(_player){
                list[stone].checkcase[0].needcase = true;
                list[stone].flag = true;
            }
        }
        if (lastused != 1 && stone - _cases[1] >= 0) {
            _player = 0;
            Play(1, stone - _cases[1], level + 1, pass1, pass2);
            lose = false;
            if(_player){
                list[stone].checkcase[1].needcase = true;
                list[stone].flag = true;
            }
        }
        if (lastused != 2 && stone - _cases[2] >= 0) {
            Play(2, stone - _cases[2], level + 1, pass1, pass2);
            lose = false;
            _player = 0;
            if(_player){
                list[stone].checkcase[2].needcase = true;
                list[stone].flag = true;
            }
        }
        if (lastused != PASS) {
            if (pass2 && (level % 2 == 1)) {
                pass2 = false;
                Play(PASS, stone, level + 1, pass1, pass2);
                lose = false;
                _player = 0;
                if(_player){
                    list[stone].checkcase[3].needcase = true;
                    list[stone].flag = true;
                }
            }
            else if (pass1 && (level % 2 == 0)) {
                pass1 = false;
                Play(PASS, stone, level + 1, pass1, pass2);
                lose = false;
                _player = 0;
                if(_player){
                    list[stone].checkcase[3].needcase = true;
                    list[stone].flag = true;
                }
            }
        }
    }
    if (win) {
        if (_loser == 0 && ((level % 2) == 0)) {
            _loser = 1;
        }
        if (_player == 0 && ((level % 2) == 0)) {
            _player = 1;
        }
    }
    else if (lose) {
        if (_loser == 0 && (level % 2)) {
            _loser = 1;
        }
        if (_player == 0 && (level % 2)) {
            _player = 1;
        }
        if (level == 1) {
            if (lastused == PASS) {
                list[stone].flag = true;
                list[stone].checkcase[3].needcase = true;
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
    std::ifstream in("2.inp");
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

