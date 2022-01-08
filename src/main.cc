#include "GameController.h"
/**
 * TODO:
 * - Commit files
 * - MVC pattern
 * - GUI
 * - Look through all files
 * - Commit
 */

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
