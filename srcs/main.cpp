/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:18:26 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/06 18:12:07 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <app/Nibbler.hpp>
#include <interfaces/test.hpp>
#include "wrapper.hpp"
#include <ai/ai.hpp>

void *print_usage()
{
    std::cout << "Usage: ./nibbler [width] [height] [interface]" << std::endl;
    std::cout << "-width\t\tWidth of the map, " << MIN_MAP_WIDTH << "-" << MAX_MAP_WIDTH << std::endl;
    std::cout << "-height\t\tHeight of the map, " << MIN_MAP_HEIGHT << "-" << MAX_MAP_HEIGHT << std::endl;
    std::cout << "-interface\tInterface to use, " << INTERFACE1 << ", " << INTERFACE2 << ", " << INTERFACE3 << std::endl;
    return (NULL);
}

void *print_error(std::string error)
{
    std::cout << "Error: " << error << std::endl;
    return (NULL);
}

Nibbler *parse_args(int argc, const char **argv)
{
    if (argc != 4)
        return (Nibbler *)(print_usage());
    if (std::stoi(argv[1]) < MIN_MAP_WIDTH || std::stoi(argv[1]) > MAX_MAP_WIDTH)
        return (Nibbler *)(print_error("Incorrect width"));
    if (std::stoi(argv[2]) < MIN_MAP_HEIGHT || std::stoi(argv[2]) > MAX_MAP_WIDTH)
        return (Nibbler *)(print_error("Incorrect height"));
    if (std::string(argv[3]) != INTERFACE1 && std::string(argv[3]) != INTERFACE2 && std::string(argv[3]) != INTERFACE3)
        return (Nibbler *)(print_error("Incorrect interface"));
    return (new Nibbler(std::stoi(argv[1]), std::stoi(argv[2]), std::string(argv[3])));
}

game_t get_map(Nibbler &game)
{
    game_t game_infos;
    game_infos.snake.push_back(std::make_pair(game.getSnake()->getY(), game.getSnake()->getX()));
    for (int i = 0; i < game.getSnake()->getBody().size(); i++)
    {
        game_infos.snake.push_back(std::make_pair(game.getSnake()->getBody()[i].getY(), game.getSnake()->getBody()[i].getX()));
    }
    for (auto &food : game.getFoods())
    {
        food_t to_add;
        to_add.y = food.getY();
        to_add.x = food.getX();
        to_add.type = food.getType();
        game_infos.foods.push_back(to_add);
    }
    for (auto &obstacle : game.getObstacles())
    {
        game_infos.obstacles.push_back({obstacle.getY(), obstacle.getX()});
    }
    game_infos.snake_direction = game.getSnake()->getDirection();
    game_infos.score = game.getScore();
    return (game_infos);
}

/*
** A placer dans une classe Game, (nibbler j'imagine)
*/
Nibbler *_game = nullptr;
library_t _current_lib, _new_lib;
std::string _lib_path;
ILibs *_interface = nullptr;
IALibs *_interface_audio = nullptr;
lib_parameter_t _parameter;
Wrapper *_wrapper = nullptr;
bool _continue = true;

void inputHandler(input_t const &input)
{
    _game->getSnake()->changeDirection(input);
    if (input == QUIT)
        _continue = false;
    else if (input == LIB1)
        _new_lib = NCURSES;
    else if (input == LIB2)
        _new_lib = SFML;
    else if (input == LIB3)
        _new_lib = OPENGL;
}

int end_game(void)
{
    if (_interface != nullptr)
        _wrapper->unloadLibrary(_interface);
    if (_interface_audio != nullptr)
        _wrapper->unloadAudioLibrary(_interface_audio);
    if (_wrapper != nullptr)
        delete _wrapper;
    return (0);
}

void gameloop(Nibbler &game)
{
    srand(time(NULL));
    _game = &game;
    _current_lib = game.getInterface();
    _new_lib = _current_lib;

    /* Map Array */
    game_t game_infos = get_map(game);

    /* Setup variables */
    uint32_t fps = 13;

    /* Init Wrapper */
    _wrapper = new Wrapper();

    /* Get Library Path */
    std::string lib_path = _wrapper->getLibraryPath(_current_lib);
    std::string lib_audio_path = _wrapper->getLibraryPath(LIBAUDIO);

    /* Default Parameter for 'current_lib' */
    _parameter = (lib_parameter_t){(uint32_t)game.getMapWidth(), (uint32_t)game.getMapHeight(), fps, inputHandler};

    _wrapper->loadLibrary(lib_path, _parameter);
    _wrapper->loadAudioLibrary(lib_audio_path);

    /* Get Interface */
    _interface = _wrapper->getInterface();
    _interface_audio = _wrapper->getAudioInterface();
    // return (__debug(interface, wrapper));

    // end_game();
    // return;
    /* Update Map through Library loaded */
    _interface->update(game_infos);
    _interface_audio->playMusic(AUDIO_GAME_MUSIC);

    /* Wail till escape character */
    while (_continue == true && game.getGameover() < PITY_AMOUNT)
    {
        _interface->update(game_infos);

        game.moveSnake();
        if (rand() % CHANCE_TO_DESPAWN_MALUS_FOOD == 0)
            game.removeMalusFood();
        if (game.isFood(game.getSnake()->getY(), game.getSnake()->getX()))
        {
            food_type_t food_type = game.getFoodType(game.getSnake()->getY(), game.getSnake()->getX());
            if (food_type == NORMAL)
            {
                game.getSnake()->grow(1);
                game.setScore(game.getScore() + FOOD_SCORE);
                _interface_audio->playSound(AUDIO_EAT_NORMAL_FOOD);
            }
            else if (food_type == BONUS)
            {
                game.getSnake()->grow(3);
                game.setScore(game.getScore() + BONUS_FOOD_SCORE);
                _interface_audio->playSound(AUDIO_EAT_BONUS_FOOD);
            }
            else if (food_type == MALUS)
            {
                game.setScore(game.getScore() + MALUS_FOOD_SCORE);
                _interface_audio->playSound(AUDIO_EAT_MALUS_FOOD);
            }
            game.removeFood(game.getSnake()->getY(), game.getSnake()->getX());
            if (rand() % CHANCE_TO_SPAWN_OBSTACLE == 0)
            {
                game.generateRandomObstacle();
                _interface_audio->playSound(AUDIO_OBSTACLE_SPAWN);
            }
        }
        if (game.getFoods().size() < MAX_FOODS)
            if (rand() % CHANCE_TO_SPAWN_FOOD == 0)
            {
                if (rand() % CHANCE_TO_SPAWN_BONUS == 0)
                {
                    game.generateRandomFood(food_type_t::BONUS);
                    _interface_audio->playSound(AUDIO_BONUS_FOOD_SPAWN);
                }
                else if (rand() % CHANCE_TO_SPAWN_MALUS == 0)
                {
                    game.generateRandomFood(food_type_t::MALUS);
                    _interface_audio->playSound(AUDIO_MALUS_FOOD_SPAWN);
                }
                else
                {
                    game.generateRandomFood(food_type_t::NORMAL);
                    _interface_audio->playSound(AUDIO_NORMAL_FOOD_SPAWN);
                }
            }
        game_infos = get_map(game);

        if (_new_lib != _current_lib)
        {
            _current_lib = _new_lib;
            lib_path = _wrapper->getLibraryPath(_current_lib);
            _interface = _wrapper->switchInterface(_interface, lib_path, _parameter);
            _interface->update(game_infos);
        }
    }

    std::cout << "Score: " << game.getScore() << "!" << std::endl;

    /* Unload Library */
    _wrapper->unloadLibrary(_interface);
    _wrapper->unloadAudioLibrary(_interface_audio);
    delete _wrapper;
}

int main(int argc, const char **argv)
{
    Nibbler *game = parse_args(argc, argv);
    if (game == NULL)
        return (1);
    try
    {
        gameloop(*game);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    delete game;
    return (0);
}
