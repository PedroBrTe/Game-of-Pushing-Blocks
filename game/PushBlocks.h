#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <random>

class PushBlocks {
public:
    /**
     * @brief Constructor for the PushBlocks class.
     * @param max_x Maximum size on the x-axis of the map.
     * @param max_y Maximum size on the y-axis of the map.
     * Initializes the game with a custom map size.
     */
    explicit PushBlocks(int max_x = 10, int max_y = 10);

    /**
     * @brief Generates the map, used at the start of the game and when you want to regenerate the map without losing your level.
     */
    void loadGame();

    /**
     * @brief Displays the map.
     */
    void displayMap();

    /**
     * @brief Gets the objects to their positions on the map.
     */
    void loadAll();

    /**
     * @brief Handles character movement upward.
     */
    void moveUp();

    /**
     * @brief Handles character movement downward.
     */
    void moveDown();

    /**
     * @brief Handles character movement to the right.
     */
    void moveRight();

    /**
     * @brief Handles character movement to the left.
     */
    void moveLeft();

    /**
     * @brief Gets the box index by its X and Y position.
     * @param x position.
     * @param y position.
     * @return The index of the box.
     */
    int getBoxIndex(int x, int y);

    /**
     * @brief Gets the finish index by its X and Y position.
     * @param x position.
     * @param y position.
     * @return The index of the finish point.
     */
    int getFinishIndex(int x, int y);

    /**
     * @brief Gets the current level.
     * @return The current level.
     */
    int get_level();

    /**
     * @brief Returns whether the user is in a win state (finished the level).
     * @return True if the user won, false otherwise.
     */
    bool win();

    /**
     * @brief Returns the map so you can manage it.
     * @return The game map.
     */
    std::vector<std::vector<std::string>> get_map();

private:
    int level = 1;

    int map_x = 10;
    int map_y = 10;

    std::string char_c = "😎";
    std::string box_c = "⬛";
    std::string blank_c = "⬜";
    std::string finish_c = "🟩";

    int char_x;
    int char_y;

    int last_char_x = char_x;
    int last_char_y = char_y;

    bool has_win = false;

    std::vector<std::vector<int>> box_cor;

    std::vector<std::vector<int>> finish_cor;

    std::vector<std::vector<std::string>> map;

    /**
     * @brief Creates the game map.
     */
    void createMap();

    /**
     * @brief Initializes the map.
     */
    void initMap();

    /**
     * @brief Initializes the box positions.
     */
    void initBoxes();

    /**
     * @brief Initializes the finish positions.
     */
    void initFinishPositions();

    /**
     * @brief Increase the level variable
     */
    void upLevel();

    /**
     * @brief Generates a random number in the range [min, max].
     * @param min Minimum value.
     * @param max Maximum value.
     * @return The randomly generated number.
     */
    int getRandom(int min, int max);
};
