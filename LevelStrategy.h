#ifndef LEVELSTRATEGY 
#define LEVELSTRATEGY 

#include "Block.h" 
#include <iostream>
#include <vector>
#include <string>
#include <random>

class LevelStrategy {
    public: 
        LevelStrategy() = default; 
        LevelStrategy(int); 
        virtual ~LevelStrategy(); 

        // the following random methods should only be called in Levels 3 and 4
        void setRandom();
        void unsetRandom(std::string);
        bool isRandomSet();

        virtual Block getNextBlock() = 0;

        // methods for level 4
        virtual void resetRowNotClearedCount(); 
        virtual void incrementRowNotClearedCount(); 
        virtual bool checkRowNotClearedCount();

        void setSeed(int);

    protected: 
        std::vector<char> _blockList; 
        bool _random;
        int _blockIndex, _seed;
        void _readBlockFile(std::string);
        Block _getNextStoredBlock();
}; 

class Level0Strategy : public LevelStrategy {
    public: 
        Level0Strategy(); 
        Level0Strategy(std::string); 
        ~Level0Strategy(); 
        Block getNextBlock(); 
        void setCommandFile(std::string);
    
}; 

class Level1Strategy : public LevelStrategy {
    public: 
        Level1Strategy(); 
        ~Level1Strategy(); 
        Block getNextBlock(); 
}; 

class Level2Strategy : public LevelStrategy {
    public: 
        Level2Strategy(); 
        ~Level2Strategy(); 
        Block getNextBlock(); 
}; 

class Level3Strategy : public LevelStrategy {
    public: 
        Level3Strategy(); 
        ~Level3Strategy(); 
        Block getNextBlock(); 
}; 

class Level4Strategy : public LevelStrategy {
    public: 
        Level4Strategy(); 
        ~Level4Strategy(); 
        Block getNextBlock(); 
        void resetRowNotClearedCount(); 
        void incrementRowNotClearedCount(); 
        bool checkRowNotClearedCount(); // returns true if rowNotClearCount % 5 == 0 
    private: 
        int _rowNotClearedCount; 
}; 

#endif 