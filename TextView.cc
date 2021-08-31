#include <iostream>
#include <iomanip> 
#include <string>
#include "TextView.h"
#include "Board.h"

// Function that gets the intial configuration of a given type of block
std::vector<std::vector<char>> TextView::_getBlockVector(char type) {
    switch(type) {
        case 'I':
            return {
                {' ', ' ', ' ', ' '},
                {'I', 'I', 'I', 'I'}
            };
        case 'J':
            return {
                {'J', ' ', ' '},
                {'J', 'J', 'J'}
            };
        case 'L':
            return {
                {' ', ' ', 'L'},
                {'L', 'L', 'L'}
            };
        case 'O':
            return {
                {'O', 'O'},
                {'O', 'O'}
            };
        case 'S':
            return {
                {' ', 'S', 'S'},
                {'S', 'S', ' '}
            };
        case 'Z':
            return {
                {'Z', 'Z', ' '},
                {' ', 'Z', 'Z'}
            };
        case 'T':
            return {
                {'T', 'T', 'T'},
                {' ', 'T', ' '}
            };   
    }
}

// Constructors & Destructor
TextView::TextView() {}
TextView::~TextView() {}

void TextView::render() {
    // Upper info
    std::cout << std::setw(4) << "" << "Level:" << std::setw(7) << _level << std::endl;
    std::cout << std::setw(4) << "" << "Score:" << std::setw(7) << _score << std::endl;
    std::cout << std::setw(4) << "" << "Hi-Score:" << std::setw(4) << _highScore << std::endl;

    // Board
    std::cout << *_board;
    std::cout << std::setw(4) << "" << "Next:" << std::endl;

    // Print the next block aligned to the right of a 2x5 rectangle
    std::vector<std::vector<char>> nextBlockVector = _getBlockVector(_nextBlock.getType());

    std::string firstRowString = "";

    // first row of Next Block
    for (auto c : nextBlockVector[0]) {
        firstRowString += c;
    }
    std::cout << std::setw(9) << firstRowString << std::endl;

    // second row of Next Block
    std::string secondRowString = "";
    for (auto c : nextBlockVector[1]) {
        secondRowString += c;
    }
    std::cout << std::setw(9) << secondRowString << std::endl;
}
