#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Constants.h"

class Block;
class Command;

class Board {
    public:
        Board();
        ~Board();
        std::vector<std::vector<char>> getBoard() const;
        Block getCurrentBlock() const;
        Block getNextBlock() const;
        void setLevel(int);
        int getLevel() const;
        
        int getScore() const;
        int getHighScore() const;
        void setHighScore(int);

        void setCurrentBlock(Block);
        void setNextBlock(Block);
        void addNewBlock(Block);
        bool play(Command);
        bool isFull() const;
        void addStarBlock();
        bool wasRowCleared() const;
        int getLastDroppedBlockLevel() const;

    private:
        int _score;
        int _highScore;
        int _level;
        int _lastDroppedBlockLevel;
        bool _gameOver;
        bool _rowCleared;
        bool _move(Block&, Command);
        bool _rotate(Block&, Command);
        bool _dropCurrent();
        bool _drop(Block&); // needed for star block

        int _numFilledRows();
        void _drawBlock(std::vector<std::vector<int>>, char, const std::pair<int, int>&, const std::pair<int, int>&, const std::pair<int, int>&);
        bool _isValidMove(Block, Command);
        bool _isValidRotate(Block, Command);
        std::vector<std::vector<char>> _board;
        std::vector<Block> _droppedBlocks; // all dropped blocks present in board
        std::vector<Block> _currentBlock; // TODO eventually change to smart pointer
        std::vector<Block> _nextBlock; // TODO eventually change to smart pointer
};
std::ostream& operator<<(std::ostream&, const Board&);
#endif
