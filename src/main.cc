#include "GameController.h"

int main(int argc, char** argv) {
    GameController* gc = GameController::createGame();
    gc->parseInitialInputs(argc, argv);
    gc->displayViews();
    while (!gc->finished()) {
        gc->readCommand();
        if (gc->runCommand()) gc->displayViews();  
    }
    return 0;
}
