#include "View.h"
#include "Board.h"

// Constructor & Destructor 
View::View() {}
View::~View() {}

// Accessor for highest score
void View::setHighScore(int score) {
    _highScore = score;
}

void View::update(int level, int score, int highScore, Block nextBlock) {
    _level = level;
    _score = score;
    _highScore = highScore;
    _nextBlock = nextBlock;
}

void View::setBoard(Board* b) {
    _board = b;
}
