#include "GameController.h"
#include "Type.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <random>

// Private Constructor for GameController 
GameController::GameController() : _textOnly{false}, _finished{false}, _restart{false}, _seed{0}, _level{0}, _highScore{0}, _scriptFile{"sequence.txt"} {
    _board = new Board();
    _textView = new TextView();
    _textView->setBoard(_board);
    _ls = new Level0Strategy();
}

GameController* GameController::createGame() {
    GameController* gc = new GameController();
    return gc;
}

// Destructor for GameController 
GameController::~GameController() {
    delete _textView;
    delete _board;
    delete _ls;
}

// function for command line interface
void GameController::parseInitialInputs(int argc, char** argv) {
    int i = 1;
    while (i < argc) {
        if (strcmp(argv[i], "-text") == 0) {
            _textOnly = true;
        }
        else if (strcmp(argv[i], "-seed") == 0) {
            if (++i == argc) break;
            _seed = atoi(argv[i]);
        }
        else if (strcmp(argv[i], "-scriptfile") == 0) {
            if (++i == argc) break;

            std::string file(argv[i]);
            _scriptFile = file;
            std::ifstream fin(file);
            if (!fin.is_open()) {
                _scriptFile = "sequence.txt";
            } else {
                fin.close();
            }
        }
        else if (strcmp(argv[i], "-startlevel") == 0) {
            if (++i == argc) break;
            _level = atoi(argv[i]);
            if (_level < 0 || _level > 4) _level = 0;
        }
        i++;
    }
    _setLS();
    _initializeBoard();
}

// Board Initialization 
void GameController::_initializeBoard(){
    _board->setLevel(_level);
    _board->setCurrentBlock(_ls->getNextBlock());
    _board->setNextBlock(_ls->getNextBlock());
}

// function to change level strategy at runtime 
void GameController::_setLS() {
    delete _ls;
    switch (_level) {
        case 0:
            _ls = new Level0Strategy(_scriptFile);
            break;
        case 1:
            _ls = new Level1Strategy();
            break;
        case 2:
            _ls = new Level2Strategy();
            break;
        case 3:
            _ls = new Level3Strategy();
            break;
        case 4:
            _ls = new Level4Strategy();
            break;        
    }
    _ls->setSeed(_seed);
}

// Function to read command from user input 
void GameController::readCommand() {
    // if there are file commands left, use them
    if (_commandStack.size() > 0) {
        _comm = _commandStack.top();
        _commandStack.pop();
        return;
    } else {
        _comm.type = EMPTY;
    }
    // otherwise read in a command from cin
    do {
        std::cout << "Please enter a command: ";
        std::cin >> _comm;
        std::cout << std::endl;
    } while (_comm.multiplier == 0);

}

// Function to check if the passed in file is valid
bool GameController::_isFileValid(std::string file) {
    std::ifstream fin(file);
    if (fin.is_open()) {
        fin.close();
        return true;
    }
    return false;
}

// Function to read command from file 
void GameController::_readCommandsFromFile(std::string file) {
    if (!_isFileValid(file)) {
        std::cout << "Invlaid file given" << std::endl;
        return;
    }

    std::ifstream fin(file);
    Command c;
    std::vector<Command> tempCommands;
    while (fin >> c) {
        tempCommands.push_back(c);
    }
    fin.close();

    for (int i = 0; i < _comm.multiplier; i++) {
        for (auto it = tempCommands.crbegin() ; it != tempCommands.crend(); ++it) {
            _commandStack.push(*it);
        }
    }
}

// Execute command 
bool GameController::runCommand() {
    std::vector<Type> boardMoves = {LEFT, RIGHT, DOWN, CLOCKWISE, COUNTERCLOCKWISE, DROP};
    
    // board moves
    if (std::find(boardMoves.begin(), boardMoves.end(), _comm.type) != boardMoves.end()) {
        if (_comm.type != DROP && !_board->play(_comm)) {
            std::cout << "That move did nothing!" << std::endl;
            return false;
        } else if (_comm.type == DROP) {
            for (int i = 0; i < _comm.multiplier; i++) {
                _board->play(_comm);
                if (_board->wasRowCleared() || _board->getLastDroppedBlockLevel() != 4) {
                    _ls->resetRowNotClearedCount();
                } else {
                    _ls->incrementRowNotClearedCount();
                }

                if (_ls->checkRowNotClearedCount()) {
                    _board->addStarBlock();
                }
                _board->setNextBlock(_ls->getNextBlock());

                if (_board->isFull()) break; // stop if game is over
            }
        }
    // level up
    } else if (_comm.type == LEVELUP) {
        if (_level == 4) {
            std::cout << "You cannot level up since you are at level 4!" << std::endl;
            return false;
        }

        _level = std::min(_level + _comm.multiplier, 4);
        _setLS();
        _board->setLevel(_level);
    // level down
    } else if (_comm.type == LEVELDOWN) {
        if (_level == 0) {
            std::cout << "You cannot level down since you are at level 0!" << std::endl;
            return false;
        }
        _level = std::max(_level - _comm.multiplier, 0);        
        _setLS();
        _board->setLevel(_level);  
    // change randomness of block generation to no random 
    } else if (_comm.type == NORANDOM) {
        if (_level < 3) {
            std::cout << "This command can only be used in level 3 and 4!" << std::endl;
            return false;
        } else if (!_isFileValid(_comm.secondArg)) {
            std::cout << "Invalid file given!" << std::endl;
            return false;
        } else if (!_ls->isRandomSet()) {
            std::cout << "Randomness is already not set!" << std::endl;
            return false;
        }
        _ls->unsetRandom(_comm.secondArg);
    // chagne to random block generation
    } else if (_comm.type == RANDOM) {
        if (_level < 3) {
            std::cout << "This command can only be used in level 3 and 4!" << std::endl;
            return false;
        } else if (_ls->isRandomSet()) {
            std::cout << "Randomness is already set!" << std::endl;
            return false;
        }
        _ls->setRandom();
    // read from file 
    } else if (_comm.type == SEQUENCE) {
        _readCommandsFromFile(_comm.secondArg);
        return false;
    // read current block
    } else if (_comm.type == BLOCK) {
        char t = _comm.secondArg[0];
        bool heavy = false;
        if (_level == 4 || _level == 3 ){
            heavy = true;
        }
        Block b{t, _level, heavy};
        _board->setCurrentBlock(b);
    // restart
    } else if (_comm.type == RESTART) {
        _restart = true;
    // error handling
    } else {
        std::cout << "Invalid Command!" << std::endl;
        return false;
    }

    // this part is executed when board is full 
    if (_board->isFull()) {
        displayViews();
        std::cout << "Game over!" << std::endl;
        std::string input;
        std::cout << "Do you wish to restart (y for 'yes', any other key for 'no'): ";
        std::cin >> input;
        if (input == "y") {
            _restart = true;
        } else {
            _finished = true;
            return false;
        }
    }

    // restart and re-initialize 
    if (_restart) {
        _highScore = _board->getHighScore();
        
        delete _board;
        _board = new Board();
        _board->setHighScore(_highScore);
        delete _textView;
        _textView = new TextView();
        _textView->setBoard(_board);

        // intialize with level 0 on a restart
        _level = 0;
        _setLS();
        _initializeBoard();
        _restart = false;
    }

    return true;
}

// display view function
void GameController::displayViews() {
    _textView->update(_level, _board->getLevel(), _highScore, _board->getNextBlock());
    _textView->render();
    std::cout << std::endl;
}

// Accessor for finished, check if the game should end 
bool GameController::finished() {
    return _finished;
}

// Accessor for restart, check if game should be restarted
bool GameController::restart() {
    return _restart;
}