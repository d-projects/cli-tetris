#include "LevelStrategy.h" 

#include <iostream> 
#include <vector> 
#include <fstream>
#include <cstdlib>
#include <random>
#include <ctime>

// Constructors 
Level0Strategy::Level0Strategy() {}

Level0Strategy::Level0Strategy(std::string file) {
    _readBlockFile(file);
}

Level1Strategy::Level1Strategy() {}

Level2Strategy::Level2Strategy() {}

Level3Strategy::Level3Strategy() {
    _random = true;
}

Level4Strategy::Level4Strategy() {
    _rowNotClearedCount = 0;
    _random = true;
}


// Destructors
LevelStrategy::~LevelStrategy() {}

Level0Strategy::~Level0Strategy() {}

Level1Strategy::~Level1Strategy() {}

Level2Strategy::~Level2Strategy() {}

Level3Strategy::~Level3Strategy() {}

Level4Strategy::~Level4Strategy() {}


// Helper functions
void LevelStrategy::_readBlockFile(std::string file) {
    std::ifstream fin (file); 
    std::vector<char> result;
    if (fin.is_open()) {
        std::string line; 
        while (getline(fin, line)) {
            while (line.size() != 0) {
                if (line.at(0) != ' ') {
                    result.push_back(line.at(0)); 
                } 
                line = line.substr(1); 
            }
        }
        fin.close(); 
    }
    _blockList = result; 
    _blockIndex = 0;
}

// fetch the next expected block 
Block LevelStrategy::_getNextStoredBlock() {
    Block next = Block(_blockList[_blockIndex++]); 
    _blockIndex %= _blockList.size();
    return next;
}


// Mutators
void LevelStrategy::setRandom() {
    _random = true;
}

void LevelStrategy::unsetRandom(std::string file) {
    _random = false;
    _readBlockFile(file);
}


void Level0Strategy::setCommandFile(std::string file) {
    _readBlockFile(file);
}

void LevelStrategy::setSeed(int seed) {
    _seed = seed;
}


// Accessors
bool LevelStrategy::isRandomSet() {
    return _random;
}

Block Level0Strategy::getNextBlock() {
    return _getNextStoredBlock();
}

Block Level1Strategy::getNextBlock() {
    static std::mt19937 rng(_seed);
    int num = rng() % 12; 
    Block result; 
    if (num == 0) {
        result = Block('S', 1, false); 
    } else if (num == 1 || num == 2) {
        result = Block('I', 1, false); 
    } else if (num == 3 || num == 4) {
        result = Block('J', 1, false); 
    } else if (num == 5 || num == 6) {
        result = Block('L', 1, false); 
    } else if (num == 7 || num == 8) {
        result = Block('O', 1, false); 
    } else if (num == 9 || num == 10) {
        result = Block('T', 1, false); 
    } else {
        result = Block('Z', 0, false); 
    }
    return result; 
}

Block Level2Strategy::getNextBlock() {
    static std::mt19937 rng(_seed);
    int num = rng() % 7; 
    Block result; 
    if (num == 0) {
        result = Block('I', 2, false); 
    } else if (num == 1) {
        result = Block('J', 2, false); 
    } else if (num == 2) {
        result = Block('L', 2, false); 
    } else if (num == 3) {
        result = Block('S', 2, false); 
    } else if (num == 4) {
        result = Block('Z', 2, false); 
    } else if (num == 5) {
        result = Block('O', 2, false); 
    } else {
        result = Block('T', 2, false); 
    }
    return result; 
}

Block Level3Strategy::getNextBlock() {
    if (!_random) {
        return _getNextStoredBlock();
    }

    static std::mt19937 rng(_seed);
    int num = rng() % 9; 
    Block result; 
    if (num == 0 || num == 1) {
        result = Block('S', 3, true); 
    } else if (num == 2) {
        result = Block('I', 3, true); 
    } else if (num == 3) {
        result = Block('J', 3, true); 
    } else if (num == 4) {
        result = Block('L', 3, true); 
    } else if (num == 5) {
        result = Block('O', 3, true); 
    } else if (num == 6) {
        result = Block('T', 3, true); 
    } else {
        result = Block('Z', 3, true); 
    }
    return result; 
}

Block Level4Strategy::getNextBlock() {
    if (!_random) {
        return _getNextStoredBlock();
    }

    static std::mt19937 rng(_seed);
    int num = rng() % 9; 
    Block result; 
    if (num == 0 || num == 1) {
        result = Block('S', 4, true); 
    } else if (num == 2) {
        result = Block('I', 4, true); 
    } else if (num == 3) {
        result = Block('J', 4, true); 
    } else if (num == 4) {
        result = Block('L', 4, true); 
    } else if (num == 5) {
        result = Block('O', 4, true); 
    } else if (num == 6) {
        result = Block('T', 4, true); 
    } else {
        result = Block('Z', 4, true); 
    }
    return result; 
}

// setter, increment, check function for rowNotClearedCount
void LevelStrategy::resetRowNotClearedCount() {}
void LevelStrategy::incrementRowNotClearedCount() {}
bool LevelStrategy::checkRowNotClearedCount() {
    return false;
}

void Level4Strategy::resetRowNotClearedCount() {
    _rowNotClearedCount = 0; 
}

void Level4Strategy::incrementRowNotClearedCount() {
    _rowNotClearedCount++; 
}

bool Level4Strategy::checkRowNotClearedCount() {
    return (_rowNotClearedCount > 0 && _rowNotClearedCount % 5 == 0); 
}