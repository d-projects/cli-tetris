// #include <memory>
#include "Constants.h"
#include "Block.h"
#include "Command.h"
#include "Board.h"
#include "Type.h"

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

Block::Block(char type, int level, bool heavy): _heavy{heavy}, _levelGenerated{level}, _type{type}, _rotation{0}, _fixedPoint{3, 0} {
    if (type == 'I'){
        // row, col
        _bottomLeft = {3, 0};
        _rotatedDimensions = {1, 4};
        _originalDimensions = {1, 4};
        _originalBlock = {
            {1, 1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
        };
    } else if (type == 'J'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 0, 0},
            {1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 1, 0},
        };
    } else if (type == 'L'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {0, 0, 1},
            {1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
        };
    } else if (type == 'O') {
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 2};
        _originalDimensions = {2, 2};
        _originalBlock = {
            {1, 1},
            {1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
        };
    } else if (type == 'S'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {0, 1, 1},
            {1, 1, 0},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
        };
   } else if (type == 'Z'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 1, 0},
            {0, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
        };
    } else if (type == 'T'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 1, 1},
            {0, 1, 0},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
        };
    } else if (type == '*'){
        // row, col
        _bottomLeft = {3, 5};
        _rotatedDimensions = {1, 1};
        _originalDimensions = {1, 1};
        _originalBlock = {
            {1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
        };
    } else {
        // TODO proper errors here
        std::cout << "Block type does not exist" << std::endl;
        throw;
    }

}


Block::Block(char type): _heavy{false}, _levelGenerated{0}, _type{type}, _rotation{0}, _fixedPoint{3, 0} {
    if (type == 'I'){
        // row, col
        _bottomLeft = {3, 0};
        _rotatedDimensions = {1, 4};
        _originalDimensions = {1, 4};
        _originalBlock = {
            {1, 1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
        };
    } else if (type == 'J'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 0, 0},
            {1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 1, 1, 0},
        };
    } else if (type == 'L'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {0, 0, 1},
            {1, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 1, 0},
            {1, 1, 1, 0},
        };
    } else if (type == 'O') {
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 2};
        _originalDimensions = {2, 2};
        _originalBlock = {
            {1, 1},
            {1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
        };
    } else if (type == 'S'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {0, 1, 1},
            {1, 1, 0},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
        };
   } else if (type == 'Z'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 1, 0},
            {0, 1, 1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
        };
    } else if (type == 'T'){
        // row, col
        _bottomLeft = {4, 0};
        _rotatedDimensions = {2, 3};
        _originalDimensions = {2, 3};
        _originalBlock = {
            {1, 1, 1},
            {0, 1, 0},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
        };
    } else if (type == '*'){
        // row, col
        _bottomLeft = {3, 5};
        _rotatedDimensions = {1, 1};
        _originalDimensions = {1, 1};
        _originalBlock = {
            {1},
        };
        _cells = {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 0, 0},
        };
    } else {
        // TODO proper errors here
        std::cout << "Block type does not exist" << std::endl;
        throw;
    }

}
Block::~Block(){

}

std::pair<int, int> Block::getBottomLeft() const{
    return _bottomLeft;
}

void Block::setBottomLeft(int r, int c){
    _bottomLeft.first = r;
    _bottomLeft.second = c;
}

std::pair<int, int> Block::getRotatedDimensions() const{
    return _rotatedDimensions;
}

void Block::setRotatedDimensions(int r, int c){
    _rotatedDimensions.first = r;
    _rotatedDimensions.second = c;
}

std::pair<int, int> Block::getOriginalDimensions() const{
    return _originalDimensions;
}

std::pair<int, int> Block::getFixedPoint() const{
    return _fixedPoint;
}

void Block::setFixedPoint(int r, int c){
    _fixedPoint.first = r;
    _fixedPoint.second = c;
}

std::vector<std::vector<int>> Block::getCells() const{
    return _cells;
}

int Block::getRotation() const {
    return _rotation;
}

int Block::getLevelGenerated() const {
    return _levelGenerated;
}

void Block::move(Command c){
    switch(c.type){
        case LEFT:
            _bottomLeft.second -=1;
            break;
        case RIGHT:
            _bottomLeft.second +=1;
            break;
        case DOWN:
            _bottomLeft.first +=1;
            break;
        default:
            break;
    }
}

bool Block::isHeavy() const {
    return _heavy;
}

// 1 for cw, -1 for ccw
void Block::rotate(Command c){
    int side;
    if (c.type == CLOCKWISE){
        side = 1;
    } else if (c.type == COUNTERCLOCKWISE){
        side = -1;
    }
    // clear original rotated array
    for(int r = 0; r < _originalDimensions.first; r++){
        for (int c = 0; c < _originalDimensions.second; c++){
            if (_rotation == 0){
                _cells[_fixedPoint.first + r - _originalDimensions.first + 1][_fixedPoint.second + c] = 0;
            } else if (_rotation == 1){
                _cells[_fixedPoint.first + c - _originalDimensions.second + 1][_fixedPoint.second - r + _originalDimensions.first - 1] = 0;
            } else if (_rotation == 2){
                _cells[_fixedPoint.first - r][_fixedPoint.second - c + _originalDimensions.second - 1] = 0;
            } else if (_rotation == 3){
                _cells[_fixedPoint.first - c][_fixedPoint.second + r] = 0;
            }
        }
    }
    _rotation += side;
    // limits
    if (_rotation < 0){
        _rotation = 3;
    } else if (_rotation > 3){
        _rotation = 0;
    }
    
    for(int r = 0; r < _originalDimensions.first; r++){
        for (int c = 0; c < _originalDimensions.second; c++){
            if (_rotation == 0){
                _cells[_fixedPoint.first + r - _originalDimensions.first + 1][_fixedPoint.second + c] = _originalBlock[r][c];
            } else if (_rotation == 1){
                _cells[_fixedPoint.first + c - _originalDimensions.second + 1][_fixedPoint.second - r + _originalDimensions.first - 1] = _originalBlock[r][c];
            } else if (_rotation == 2){
                _cells[_fixedPoint.first - r][_fixedPoint.second - c + _originalDimensions.second - 1] = _originalBlock[r][c];
            } else if (_rotation == 3){
                _cells[_fixedPoint.first - c][_fixedPoint.second + r] = _originalBlock[r][c];
            }
        }
    }

    // flip dimensions
    int temp = _rotatedDimensions.first;
    _rotatedDimensions.first = _rotatedDimensions.second;
    _rotatedDimensions.second = temp;
}

char Block::getType() const{
    return _type;
}
