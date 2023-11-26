#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include "game/PushBlocks.h"


void winScreen();

void clear();

int main() {
    SetConsoleOutputCP(CP_UTF8);

    PushBlocks game;
    game.loadGame();

    while (true) {
        if (game.win()){
            winScreen();
            game.loadGame();
        }
        clear();

        std::cout << "level: " << game.get_level() << "\n";
        game.displayMap();
        std::cout << "R-Recreate Q-Exit";

        char input = tolower(_getch());

        switch (input){
            case ('w'):
                game.moveUp();
                break;
            case ('s'):
                game.moveDown();
                break;
            case ('d'):
                game.moveRight();
                break;
            case ('a'):
                game.moveLeft();
                break;

            case ('r'):
                game.loadGame();
                break;
            case ('q'):
                exit(0);
        }
    }
}

void winScreen() {
    // Print Win Screen
    char input;

    clear();
    std::cout << "      \n\n\n";
    std::cout << "      Next level!";
    std::cout << "      \n\n\n\n";
    std::cout << "   Q-EXIT C-CONTINUE\n";

    while (true) {

        do {
            input = _getch();
            if (tolower(input) == 'q') {
                exit(0);

            } else if (tolower(input) == 'c') {
                return;
            }

        } while (input!='q'<<'c');
    }
}

void clear() {
        // clear the screen
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif
}