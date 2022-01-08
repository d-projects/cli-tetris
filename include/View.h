#ifndef VIEW_H
#define VIEW_H
#include "Board.h"
#include "Block.h"

class View {
    protected:
        int _level, _score, _highScore;
        Block _nextBlock;
        Board* _board;

    public:
        View();
        virtual ~View();
        void setHighScore(int);
        void update(int level, int score, int highScore, Block nextBlock);
        void setBoard(Board* b);
        virtual void render() = 0;
};

#endif
