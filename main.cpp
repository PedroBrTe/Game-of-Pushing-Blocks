#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <random>

using namespace std;

void winScreen();

void printArray(vector<vector<string>> map, int map_x, int map_y);
void createMap(vector<vector<string>> * map,int map_x, int map_y, string blank_space);

int getRandom(int min, int max);
void clear();


int main(){
    SetConsoleOutputCP(CP_UTF8);
    while (true) {
        bool continue_game = true;

        char input;

        string char_s   = "😎";
        string box_s    = "⬛";
        string blank_s  = "⬜";
        string finish_s = "🟩";

        int map_x = 10;
        int map_y = 10;


        vector<vector<string>> map;

        createMap(&map, map_x, map_y, blank_s);

        // Get objects coordinates
        int char_x = getRandom(0, map_x-1);
        int char_y = getRandom(0, map_y-1);

        int box_x = getRandom(1, map_x-2);
        int box_y = getRandom(1, map_y-2);

        int finish_x = getRandom(0, map_x-1);
        int finish_y = getRandom(0, map_y-1);

        // Check if any overlap
        if ((char_x==box_x)&(char_y==box_y)|((box_x==finish_x)&(box_y==finish_y))|(char_x==finish_x)&(char_y==finish_y)){
            continue_game=false;
        }


        map[finish_y][finish_x] = finish_s;

         while (continue_game) {
            clear();

            int last_char_x = char_x;
            int last_char_y = char_y;


            if (box_x == finish_x & box_y == finish_y) {
                winScreen();
                break;
            }


            map[char_y][char_x] = char_s;
            map[box_y][box_x] = box_s;


            cout << "Y=" << char_y << " X=" << char_x << "\n";

            printArray(map, map_x, map_y);
            cout << "R-Recreate Q-Exit";

            input = _getch();

            switch (input) {
                case 'w':
                    // Go up
                    if ((char_y - 1 < 0)) {
                        break;
                    }

                    // Checks for box and try to push it, same for others cases
                    if (char_y - 1 == box_y & char_x == box_x) {
                        if (box_y - 1 >= 0) {
                            --box_y;
                        } else {
                            break;
                        }
                    }

                    --char_y;
                    break;

                case 'd':
                    // Go right
                    if (char_x + 1 > map_x - 1) {
                        break;
                    }

                    if (char_x + 1 == box_x & char_y == box_y) {
                        if (box_x < map_x - 1) {
                            ++box_x;
                        } else {
                            break;
                        }
                    }

                    ++char_x;
                    break;

                case 'a':
                    // Go left
                    if ((char_x - 1 < 0)) {
                        break;
                    }

                    if (char_x - 1 == box_x & char_y == box_y) {
                        if (box_x - 1 >= 0) {
                            --box_x;
                        } else {
                            break;
                        }
                    }

                    --char_x;
                    break;

                case 's':
                    // Go down
                    if ((char_y + 1 > map_y - 1)) {
                        break;
                    }

                    if (char_y + 1 == box_y & char_x == box_x) {
                        if (box_y < map_y - 1) {
                            ++box_y;
                        } else {
                            break;
                        }
                    }

                    ++char_y;
                    break;

                case 'r':
                    // Reset game
                    continue_game = false;
                    break;

                case 'q':
                    // Exit
                    exit(0);


                default:
                    break;
            }

            // Replace finish or blank square
            if (last_char_x == finish_x & last_char_y == finish_y) {
                map[last_char_y][last_char_x] = finish_s;
            } else {
                map[last_char_y][last_char_x] = blank_s;
            }

            // Delay to don't span click
            Sleep(50);
        }
    }
}


void winScreen(){
    while (true){
        clear();

        cout << "      \n\n\n";
        cout << "      You win!!!!!";
        cout << "      \n\n\n\n";
        cout << "   Q-EXIT C-CONTINUE\n";

        char input = _getch();

       if (tolower(input) == 'q'){
            exit(0);
       } else if (tolower(input) == 'c'){
           cout << "socorro.\n";
           break;
       }
   }
}



void printArray(vector<vector<string>> map, int map_x, int map_y){
    for (int line=0; line<map_y; line++){
        for (int space=0; space<map_x; space++){
            cout << map[line][space];
        }
        cout << "\n";
    }
}


void createMap(vector<vector<string>> * map,int map_x, int map_y, string blank_space){
    // Create the vector/map with the desired size
    vector<string> temp_x = {};

    for (int x=0; x<map_x;x++){
            temp_x.emplace_back(blank_space);
        }
    for (int y=0; y<map_y;y++){
        map->push_back(temp_x);
    }
}

int getRandom(int min, int max){
    random_device rd;
    uniform_int_distribution<int> dist(min, max);
    int returned = dist(rd);

    return returned;
}


void clear(){
    system("cls");
}

