#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Block.h"
#include "Constants.h"
#include "Command.h"

Board::Board(): _board(Constants::BOARD_CELL_ROWS, std::vector<char>(Constants::BOARD_CELL_COLS, ' ')),
    _gameOver{false}, _score{false}, _highScore{0}, _level{0} {
    for (int i = 0; i < Constants::BOARD_CELL_ROWS; i++){
        for (int j = 0; j < Constants::BOARD_CELL_COLS; j++){
            _board[i][j] = ' ';
        }
    }
}


Board::~Board() {}

template <typename T>
void print_2d_vector(const std::vector<std::vector<T>> &matrix){
    for(auto row_obj : matrix){
        for (auto elem: row_obj){
            std::cout<<elem<<", ";
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

bool Board::isFull() const{
    return _gameOver;
}

bool Board::play(Command c){
    
    if (c.type == LEFT || c.type == RIGHT || c.type ==  DOWN){
        bool valid1 = _move(_currentBlock[0], c);
        bool valid2;
        c.type = DOWN;
        c.multiplier = 1;
        if (_currentBlock[0].isHeavy()){
            valid2 = _move(_currentBlock[0], c);
        }
        return valid1 || valid2;
    } else if (c.type == CLOCKWISE || c.type == COUNTERCLOCKWISE){
        bool valid1 =_rotate(_currentBlock[0], c);
        bool valid2;
        c.type = DOWN;
        c.multiplier = 1;
        if (_currentBlock[0].isHeavy()){
            valid2 = _move(_currentBlock[0], c);
        }
        return valid1 || valid2;
    } else if (c.type == DROP){

        _lastDroppedBlockLevel = _currentBlock[0].getLevelGenerated();
        bool valid = _drop(_currentBlock[0]);
        addNewBlock(_nextBlock[0]);
        _nextBlock.clear();
        return valid;
    } else {
        return false;
    }
}

bool Board::_isValidMove(Block b, Command c){
    bool valid = true;
    std::pair<int, int> originalBottomLeft = b.getBottomLeft();
    std::vector<std::vector<int>> blockCells = b.getCells();
    std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
    std::pair<int, int> fixedPoint = b.getFixedPoint();

    b.move(c);
    std::pair<int, int> bottomLeft = b.getBottomLeft();
    if (bottomLeft.first < 0 || bottomLeft.first > Constants::BOARD_CELL_ROWS - 1 || 
        bottomLeft.second < 0 || bottomLeft.second + rotatedDimensions.second - 1 > Constants::BOARD_CELL_COLS - 1){
        return false;
    }
    
    _drawBlock(blockCells, ' ', rotatedDimensions, originalBottomLeft, fixedPoint);

    // check if new location is all empty
    for (int i = 0; i < rotatedDimensions.first; i++){
        for (int j = 0; j < rotatedDimensions.second; j++){
            if (blockCells[fixedPoint.first - i][fixedPoint.second + j] == 1 ){
                if (_board[bottomLeft.first - i][bottomLeft.second + j] != ' '){
                    valid = false;
                }
            }
        }
    }

    // if move is valid, we reset to the original blocks, TODO we can remove or keep this actually,
    // since now that we know the move is valid, we already clear the existing blocks and move in the
    // actual move function
    _drawBlock(blockCells, b.getType(), rotatedDimensions, originalBottomLeft, fixedPoint);

    return valid;
}

bool Board::_move(Block& b, Command c){
    for (int i = 0; i < c.multiplier; i++){
        // TODO check if possible first
        if (!_isValidMove(b, c)){
            return false;
        }
        // assuming possible move
        // values that don't change
        std::vector<std::vector<int>> blockCells = b.getCells();
        std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
        std::pair<int, int> fixedPoint = b.getFixedPoint();
        
        // changing value
        std::pair<int, int> oldBottomLeft = b.getBottomLeft();

        // remove previous location
        _drawBlock(blockCells, ' ', rotatedDimensions, oldBottomLeft, fixedPoint);

        // move currentblock
        b.move(c);
        // get new coords
        std::pair<int, int> newBottomLeft = b.getBottomLeft();
        
        // replace with new block
        _drawBlock(blockCells, b.getType(), rotatedDimensions, newBottomLeft, fixedPoint);
    }

    return true;
}

int Board::_numFilledRows(){
    int filled = 0;
    for (int i = Constants::BOARD_CELL_ROWS -1; i < Constants::BOARD_CELL_ROWS -1 + 4; i--){
        for (int j = 0; j < Constants::BOARD_CELL_COLS; j++){
            if (_board[i][j] == ' '){
                return filled;
            }
        }
        filled +=1;
    }
    return filled;
}

bool Board::_drop(Block& b){ // for star block
    Command c{DOWN};
    c.multiplier = 1;
    while (_isValidMove(b, c)){
        _move(b, c);
    }
    _droppedBlocks.push_back(b);
    int filled = _numFilledRows();

    if (filled > 0){
        _rowCleared = true;
        int topFilled = Constants::BOARD_CELL_ROWS - filled; //index of the topmost filled row
        for (Block& db: _droppedBlocks){
            std::pair<int, int> bottomLeft = db.getBottomLeft();
            std::vector<std::vector<int>> blockCells = db.getCells();

            if (bottomLeft.first >= topFilled){
                _drawBlock(blockCells, ' ', db.getRotatedDimensions(), db.getBottomLeft(), db.getFixedPoint());

                int overlap = bottomLeft.first - topFilled + 1; 
                std::pair<int, int> dimensions = db.getRotatedDimensions();
                std::pair<int, int> fixedPoint = db.getFixedPoint();

                db.setRotatedDimensions(dimensions.first - overlap, dimensions.second);
                db.setFixedPoint(fixedPoint.first - overlap, fixedPoint.second);
                db.setBottomLeft(Constants::BOARD_CELL_ROWS -1, bottomLeft.second);

                _drawBlock(blockCells, db.getType(), db.getRotatedDimensions(), db.getBottomLeft(), db.getFixedPoint());
            } else {

                _drawBlock(blockCells, ' ', db.getRotatedDimensions(), db.getBottomLeft(), db.getFixedPoint());
                db.setBottomLeft(db.getBottomLeft().first + filled, db.getBottomLeft().second);
                _drawBlock(blockCells, db.getType(), db.getRotatedDimensions(), db.getBottomLeft(), db.getFixedPoint());
            }
        }
        _score += (_level + filled) * (_level + filled);
    } else {
        _rowCleared = false;
    }

    int bonus = 0;
    _droppedBlocks.erase(std::remove_if(
        _droppedBlocks.begin(), _droppedBlocks.end(),
        [&](const Block& db) { 
            if (db.getRotatedDimensions().first <= 0){
                bonus += (db.getLevelGenerated() + 1) * (db.getLevelGenerated() + 1);
                return true;
            } else {
                return false;
            }
        }
    ), _droppedBlocks.end());

    _score += bonus;
    if (_score > _highScore){
        _highScore = _score;
    }

    std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
    std::pair<int, int> fixedPoint = b.getFixedPoint();
    std::pair<int, int> bottomLeft = b.getBottomLeft();
    char type = b.getType();
    std::vector<std::vector<int>> blockCells = b.getCells();

    for (Block& db: _droppedBlocks){
        if (db.getBottomLeft() == bottomLeft && db.getType() == type && 
        db.getRotatedDimensions() == rotatedDimensions && db.getFixedPoint() == fixedPoint){
            _drawBlock(blockCells, b.getType(), rotatedDimensions, bottomLeft, fixedPoint);
        }
    }
    return true;
}

int Board::getLastDroppedBlockLevel() const{
    return _lastDroppedBlockLevel;
}

bool Board::wasRowCleared() const {
    return _rowCleared;
}

int Board::getScore() const{
    return _score;
}

int Board::getHighScore() const{
    return _highScore;
}

void Board::setHighScore(int score){
    _highScore = score;
}

int Board::getLevel() const{
    return _level;
}

bool Board::_isValidRotate(Block b, Command c){
    bool valid = true;
    std::pair<int, int> bottomLeft = b.getBottomLeft();
    std::pair<int, int> fixedPoint = b.getFixedPoint();

    std::pair<int, int> originalDimensions = b.getOriginalDimensions();
    std::pair<int, int> originalRotatedDimensions = b.getRotatedDimensions();
    std::vector<std::vector<int>> originalBlockCells = b.getCells();
    int rotation = b.getRotation();

    // clear block first
    _drawBlock(originalBlockCells, ' ', originalRotatedDimensions, bottomLeft, fixedPoint);  

    b.rotate(c);
    std::pair<int, int> newRotatedDimensions = b.getRotatedDimensions();
    std::vector<std::vector<int>> newBlockCells = b.getCells();

    rotation = b.getRotation();

    // check if new locatio is all empty
    for (int i = 0; i < newRotatedDimensions.first; i++){
        for (int j = 0; j < newRotatedDimensions.second; j++){
            if (newBlockCells[fixedPoint.first - i][fixedPoint.second + j] == 1 ){
                if (_board[bottomLeft.first - i][bottomLeft.second + j] != ' '){
                    valid =  false;
                }
            }
        }
    }

    _drawBlock(originalBlockCells, b.getType(), originalRotatedDimensions, bottomLeft, fixedPoint);

    return valid;
}

bool Board::_rotate(Block& b, Command c){
    for (int i = 0; i < c.multiplier; i++){
        if (!_isValidRotate(b, c)){
            return false;
        }

        std::pair<int, int> bottomLeft = b.getBottomLeft();
        std::pair<int, int> originalDimensions = b.getOriginalDimensions();
        std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
        std::pair<int, int> fixedPoint = b.getFixedPoint();
        std::vector<std::vector<int>> blockCells = b.getCells();

        // assuming possible
        int rotation = b.getRotation();

        _drawBlock(blockCells, ' ', rotatedDimensions, bottomLeft, fixedPoint);

        b.rotate(c);
        blockCells = b.getCells();
        rotatedDimensions = b.getRotatedDimensions();
        fixedPoint = b.getFixedPoint();

        _drawBlock(blockCells, b.getType(), rotatedDimensions, bottomLeft, fixedPoint);
    }

    return true;
}

Block Board::getCurrentBlock() const{
    return _currentBlock[0];
}

Block Board::getNextBlock() const{
    return _nextBlock[0];
}

std::vector<std::vector<char>> Board::getBoard() const{
    return _board;
}

void Board::setLevel(int level){
    _level = level;
}


void Board::_drawBlock(std::vector<std::vector<int>> blockCells, char type, const std::pair<int, int>& dimensions, 
const std::pair<int, int>& bottomLeft, const std::pair<int, int>& fixedPoint){
    for (int i = 0; i < dimensions.first; i++){
        for (int j = 0; j < dimensions.second; j++){
            if (blockCells[fixedPoint.first - i][fixedPoint.second + j] == 1){
                _board[bottomLeft.first - i][bottomLeft.second + j] = type;
            }
        }
    }
}

void Board::addStarBlock(){
    Block b{'*', 4, false};
    std::pair<int, int> bottomLeft = b.getBottomLeft();
    std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
    std::pair<int, int> fixedPoint = b.getFixedPoint();
    std::vector<std::vector<int>> blockCells = b.getCells();

    // check if we can add a block 
    for (int i = 0; i < rotatedDimensions.first; i++){
        for (int j = 0; j < rotatedDimensions.second; j++){
            if (blockCells[fixedPoint.first - i][fixedPoint.second + j] == 1 ){
                if (_board[bottomLeft.first - i][bottomLeft.second + j] != ' '){
                    _gameOver = true;
                    return;
                }
            }
        }
    }
    _drop(b);
}

void Board::setCurrentBlock(Block b){
    if (_currentBlock.size() == 1){
        std::pair<int, int> bottomLeft = _currentBlock[0].getBottomLeft();
        std::pair<int, int> rotatedDimensions = _currentBlock[0].getRotatedDimensions();
        std::pair<int, int> fixedPoint = _currentBlock[0].getFixedPoint();
        std::vector<std::vector<int>> blockCells = _currentBlock[0].getCells();
        _drawBlock(blockCells, ' ', rotatedDimensions, bottomLeft, fixedPoint);
        _currentBlock.clear();
    }
    // better practice to first clear current block from board, but TODO
    addNewBlock(b);
}


void Board::setNextBlock(Block b){
    _nextBlock.clear();
    _nextBlock.push_back(b);
}

void Board::addNewBlock(Block b){
    std::pair<int, int> bottomLeft = b.getBottomLeft();
    std::pair<int, int> rotatedDimensions = b.getRotatedDimensions();
    std::pair<int, int> fixedPoint = b.getFixedPoint();
    std::vector<std::vector<int>> blockCells = b.getCells();

    // check if we can add a block 
    for (int i = 0; i < rotatedDimensions.first; i++){
        for (int j = 0; j < rotatedDimensions.second; j++){
            if (blockCells[fixedPoint.first - i][fixedPoint.second + j] == 1 ){
                if (_board[bottomLeft.first - i][bottomLeft.second + j] != ' '){
                    std::cout << "game over" << std::endl;
                    _gameOver = true;
                    return;
                }
            }
        }
    }
    _currentBlock.clear();
    _currentBlock.push_back(b);
    _drawBlock(blockCells, _currentBlock[0].getType(), rotatedDimensions, bottomLeft, fixedPoint);
}

std::ostream& operator<<(std::ostream& out, const Board& b){
    std::vector<std::vector<char>> board = b.getBoard();
    // print top
    // print beginning spaces
    for (int i = 0; i < 4; i++){
        out << " ";
    }
    for (int i = 0; i < 13; i++){
        out << "-";
    }
    out << std::endl;

    for (int i = 0; i < Constants::BOARD_CELL_ROWS; i++){
        if (i+1 < 10){
            out << i + 1 << "   ";
        } else{
            out << i + 1 << "  ";
        }
        for (int j = 0; j < Constants::BOARD_CELL_COLS; j++){
            out << board[i][j];
        }
        out << std::endl;
    }

    // print bottom
    // print beginning spaces
    for (int i = 0; i < 4; i++){
        out << " ";
    }
    for (int i = 0; i < 13; i++){
        out << "-";
    }
    out << std::endl;
   return out;
}
