#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
// don't need to include the class definition since we don't have a block object, only a ptr
// #include "Command.h"
#include "Constants.h"
class Command;

class Block{
    public:
        Block()=default;
        Block(char, int, bool); 
        Block(char); 
        ~Block();
        std::vector<std::vector<int> > getCells() const;
        std::pair<int, int> getBottomLeft() const;
        void setBottomLeft(int, int);

        std::pair<int, int> getRotatedDimensions() const;
        void setRotatedDimensions(int, int);

        std::pair<int, int> getOriginalDimensions() const;
        std::pair<int, int> getFixedPoint() const;
        void setFixedPoint(int, int);
        
        int getRotation() const;
        int getLevelGenerated() const;
        void move(Command);
        void rotate(Command);
        char getType() const;

        bool isHeavy() const;
    private:
        char _type;
        int _levelGenerated;
        int _rotation; // must range between 0 - 4
        bool _heavy;
        std::pair<int, int> _fixedPoint;
        std::pair<int,int> _bottomLeft;
        std::pair<int, int> _rotatedDimensions;
        std::pair<int, int> _originalDimensions;
        std::vector<std::vector<int> > _cells;
        std::vector<std::vector<int> > _originalBlock;
};
#endif