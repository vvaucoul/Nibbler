/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:15:39 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/30 14:26:43 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.hpp"
#include "ILibs.hpp"

#include <vector>
#include <array>

#include <unistd.h>

static uint32_t randBetweenMax(uint32_t min, uint32_t max)
{
    return (rand() % (max - min + 1) + min);
}

static void updateRandomMap(std::vector<std::string> &map)
{
    uint32_t max_y = 20;
    uint32_t max_x = 20;

    uint32_t x = randBetweenMax(0, max_x - 1);
    uint32_t y = randBetweenMax(0, max_y - 1);
    if (randBetweenMax(0, 1) == 0)
        map[y][x] = '.';

    x = randBetweenMax(0, max_x - 1);
    y = randBetweenMax(0, max_y - 1);
    if (randBetweenMax(0, 1) == 0)
        map[y][x] = 'X';

    x = randBetweenMax(0, max_x - 1);
    y = randBetweenMax(0, max_y - 1);
    if (randBetweenMax(0, 1) == 0)
        map[y][x] = 'O';

    x = randBetweenMax(0, max_x - 1);
    y = randBetweenMax(0, max_y - 1);
    if (randBetweenMax(0, 1) == 0)
        map[y][x] = ' ';
}

static int __debug(ILibs *interface, Wrapper *wrapper)
{
    wrapper->unloadLibrary(interface);
    delete wrapper;
    return (0);
}

static game_t __init_game(void)
{
    game_t game;

    game.snake.insert(game.snake.begin(), std::pair<int, int>(10, 10));
    game.snake.insert(game.snake.begin(), std::pair<int, int>(10, 11));
    game.snake.insert(game.snake.begin(), std::pair<int, int>(10, 12));

    game.foods.insert(game.foods.begin(), (food_t){10, 5, NORMAL});
    game.foods.insert(game.foods.begin(), (food_t){10, 15, NORMAL});
    game.foods.insert(game.foods.begin(), (food_t){5, 10, NORMAL});

    game.obstacles.insert(game.obstacles.begin(), std::pair<int, int>(5, 5));
    game.obstacles.insert(game.obstacles.begin(), std::pair<int, int>(5, 15));
    game.obstacles.insert(game.obstacles.begin(), std::pair<int, int>(15, 5));

    game.score = 0;
    game.snake_direction = UP;

    return (game);
}

static bool _continue;
static std::string _lib_path;
static library_t _current_lib;
Wrapper *wrapper;
lib_parameter_t lib_parameter;
ILibs *interface = nullptr;

static void inputHandler(input_t const &input)
{
    // game->getSnake()->changeDirection(input);
    if (input == QUIT)
        _continue = false;
    else if (input == LIB1 && _current_lib != NCURSES)
    {
        _current_lib = NCURSES;
        _lib_path = wrapper->getLibraryPath(NCURSES);
        interface = wrapper->switchInterface(interface, _lib_path, lib_parameter);
    }
    else if (input == LIB2 && _current_lib != SFML)
    {
        _current_lib = SFML;
        _lib_path = wrapper->getLibraryPath(SFML);
        interface = wrapper->switchInterface(interface, _lib_path, lib_parameter);
    }
    else if (input == LIB3 && _current_lib != OPENGL)
    {
        _current_lib = OPENGL;
        _lib_path = wrapper->getLibraryPath(OPENGL);
        interface = wrapper->switchInterface(interface, _lib_path, lib_parameter);
    }
}

int wrapper_test(void)
{
    srand(time(NULL));


    /* Map Size */
    uint32_t max_y = 20;
    uint32_t max_x = 20;
    uint32_t speed = 1;
    game_t game = __init_game();

    sleep(1);

    /* Setup variables */
    input_t input = NONE;
    library_t current_lib = library_t::SFML; // Start with Ncurses
    lib_parameter = (lib_parameter_t){max_x, max_y, speed, inputHandler};

    /* Init Wrapper */
    wrapper = new Wrapper();

    /* Get Library Path */
    std::string lib_path = wrapper->getLibraryPath(current_lib);
    wrapper->loadLibrary(lib_path, lib_parameter);

    /* Get Interface */
    interface = wrapper->getInterface();
    // return (__debug(interface, wrapper));

    /* Update Map through Library loaded */
    interface->update(game);
    sleep(1);

    /* Switch to OpenGL */
    _current_lib = OPENGL;
    _lib_path = wrapper->getLibraryPath(OPENGL);
    interface = wrapper->switchInterface(interface, _lib_path, lib_parameter);

    interface->update(game);
    sleep(1);

    /* Switch to NCURSES */
    _current_lib = NCURSES;
    _lib_path = wrapper->getLibraryPath(NCURSES);
    interface = wrapper->switchInterface(interface, _lib_path, lib_parameter);

    interface->update(game);
    sleep(1);

    wrapper->unloadLibrary(interface);
    delete wrapper;
    exit(0);

    /* Wailt till escape character */
    while (input != QUIT)
    {
        interface->update(game);

        // updateRandomMap(map);
    }

    /* Unload Library */
    wrapper->unloadLibrary(interface);
    delete wrapper;
    return (0);
}