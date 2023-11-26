#include "PushBlocks.h"


PushBlocks::PushBlocks(int max_x, int max_y) {
    map_x = max_x;
    map_y = max_y;
}



void PushBlocks::loadGame() {
    map = {};
    box_cor = {};
    finish_cor = {};

    createMap();
    initMap();

    loadAll();
}

void PushBlocks::displayMap() {
    for (int line = 0; line < map_y; line++) {
        for (int space = 0; space < map_x; space++) {
            std::cout << map[line][space];
        }
        std::cout << "\n";
    }
}

void PushBlocks::loadAll() {
    int finish_index = getFinishIndex(last_char_x, last_char_y);

    if (finish_index != -1) {
        map[last_char_y][last_char_x] = finish_c;
    } else {
        map[last_char_y][last_char_x] = blank_c;
    }

    std::vector<int> indexBoxToErase;

    for (const std::vector<int> &box_cord : box_cor) {
        int finish_index_from_box = getFinishIndex(box_cord[0], box_cord[1]);

        if (finish_index_from_box != -1) {
            int box_index = getBoxIndex(box_cord[0], box_cord[1]);
            indexBoxToErase.push_back(box_index);
        } else {
            map[box_cord[1]][box_cord[0]] = box_c;
        }
    }

    for (const int &box_index : indexBoxToErase) {
        box_cor.erase(box_cor.begin() + box_index);
    }

    for (const std::vector<int> &finish_cord : finish_cor) {
        map[finish_cord[1]][finish_cord[0]] = finish_c;
    }

    map[char_y][char_x] = char_c;

    if (box_cor.empty()) {
        upLevel();
        has_win = true;

    } else {
        has_win = false;
    }
}

void PushBlocks::moveUp() {
    if (char_y - 1 < 0) {
        return;
    }

    int boxIndex = getBoxIndex(char_x, char_y - 1);
    if (boxIndex != -1) {
        if (box_cor[boxIndex][1] - 1 >= 0 && getBoxIndex(box_cor[boxIndex][0], box_cor[boxIndex][1] - 1) == -1) {
            --box_cor[boxIndex][1];
        } else {
            return;
        }
    }

    last_char_y = char_y;
    last_char_x = char_x;

    char_y--;
    loadAll();
}

void PushBlocks::moveDown() {
    if (char_y + 1 >= map_y) {
        return;
    }

    int boxIndex = getBoxIndex(char_x, char_y + 1);
    if (boxIndex != -1) {
        if (box_cor[boxIndex][1] + 1 < map_y && getBoxIndex(box_cor[boxIndex][0], box_cor[boxIndex][1] + 1) == -1) {
            ++box_cor[boxIndex][1];
        } else {
            return;
        }
    }

    last_char_y = char_y;
    last_char_x = char_x;

    char_y++;
    loadAll();
}

void PushBlocks::moveRight() {
    if (char_x + 1 >= map_x) {
        return;
    }

    int boxIndex = getBoxIndex(char_x + 1, char_y);
    if (boxIndex != -1) {
        if (box_cor[boxIndex][0] + 1 < map_x && getBoxIndex(box_cor[boxIndex][0] + 1, box_cor[boxIndex][1]) == -1) {
            ++box_cor[boxIndex][0];
        } else {
            return;
        }
    }

    last_char_y = char_y;
    last_char_x = char_x;

    char_x++;
    loadAll();
}

void PushBlocks::moveLeft() {
    if (char_x - 1 < 0) {
        return;
    }

    int boxIndex = getBoxIndex(char_x - 1, char_y);
    if (boxIndex != -1) {
        if (box_cor[boxIndex][0] - 1 >= 0 && getBoxIndex(box_cor[boxIndex][0] - 1, box_cor[boxIndex][1]) == -1) {
            --box_cor[boxIndex][0];
        } else {
            return;
        }
    }

    last_char_y = char_y;
    last_char_x = char_x;

    char_x--;
    loadAll();
}

int PushBlocks::getBoxIndex(int x, int y) {
    int i = 0;
    for (const std::vector<int> &box_cord : box_cor) {
        if (x == box_cord[0] && y == box_cord[1]) {
            return i;
        }
        i++;
    }
    return -1;
}

int PushBlocks::getFinishIndex(int x, int y) {
    int i = 0;
    for (const std::vector<int> &finish_cord : finish_cor) {
        if (x == finish_cord[0] && y == finish_cord[1]) {
            return i;
        }
        i++;
    }
    return -1;
}

int PushBlocks::get_level() {
    return level;
}
std::vector<std::vector<std::string>> PushBlocks::get_map(){
    return map;
}

bool PushBlocks::win() {
    return has_win;
}

void PushBlocks::createMap() {
    std::vector<std::string> temp_x = {};

    for (int x = 0; x < map_x; x++) {
        temp_x.push_back(blank_c);
    }
    for (int y = 0; y < map_y; y++) {
        map.push_back(temp_x);
    }
}

void PushBlocks::initMap() {
    char_x = getRandom(0, map_x - 1);
    char_y = getRandom(0, map_y - 1);

    last_char_x = char_x;
    last_char_y = char_y;

    initBoxes();
    initFinishPositions();
}

void PushBlocks::initBoxes() {
    for (int i = 0; i < sqrt(level) * level/4; i++) {
        int box_x, box_y;

        do {
            box_x = getRandom(1, map_x - 2);
            box_y = getRandom(1, map_y - 2);
        } while ((box_x == char_x && box_y == char_y) || (getBoxIndex(box_x, box_y) != -1));

        box_cor.push_back({box_x, box_y});
    }
}

void PushBlocks::initFinishPositions() {
    int finish_x, finish_y;

    do {
        finish_x = getRandom(0, map_x - 1);
        finish_y = getRandom(0, map_y - 1);
    } while ((finish_x == char_x && finish_y == char_y) || (getBoxIndex(char_x, char_y) != -1));

    finish_cor.push_back({finish_x, finish_y});
}

void PushBlocks::upLevel() {
    ++level;
}

int PushBlocks::getRandom(int min, int max) {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(min, max);
    int random_number = dist(rd);

    return random_number;
}

