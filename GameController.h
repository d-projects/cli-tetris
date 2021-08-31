#include <string>
#include "Command.h"
#include "LevelStrategy.h"
#include "Board.h"
#include "TextView.h"
#include <stack>

class Command;
class TextView;
class Board;

class GameController {
    bool _textOnly, _finished, _restart;
    int _seed, _level, _highScore;
    std::string _scriptFile;
    Command _comm;
    TextView* _textView;
    Board* _board;
    LevelStrategy* _ls;
    std::stack<Command> _commandStack;
    void _setLS();
    void _readCommandsFromFile(std::string);
    void _initializeBoard();
    bool _isFileValid(std::string);
    GameController();

    public:
        ~GameController();
        static GameController* createGame();
        void parseInitialInputs(int, char**);
        void displayViews();
        bool runCommand();
        bool finished();
        bool restart();
        void readCommand();
};
