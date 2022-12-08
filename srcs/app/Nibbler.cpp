/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:19:19 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/06 14:53:07 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nibbler.hpp"

Nibbler::Nibbler()
:   _map_height(0),
    _map_width(0),
    _snake(new Snake()),
    _foods(std::vector<Food>()),
    _obstacles(std::vector<Obstacle>()),
    _interface(NCURSES),
    _score(0),
    _gameover(0)
{}

Nibbler::Nibbler(int map_height, int map_width, std::string interface)
:   _map_height(map_height),
    _map_width(map_width),
    _snake(new Snake(map_height / 2, map_width / 2, INITIAL_DIRECTION, INITIAL_SIZE)),
    _foods(std::vector<Food>()),
    _obstacles(std::vector<Obstacle>()),
    _score(INITIAL_SCORE),
    _gameover(0)
{
    if (interface == INTERFACE1)
        _interface = NCURSES;
    else if (interface == INTERFACE2)
        _interface = SFML;
    else if (interface == INTERFACE3)
        _interface = OPENGL;
    else
        _interface = SFML;
    for (int i = 0; i < INITIAL_OBSTACLES; i++)
        this->generateRandomObstacle();
}

Nibbler::~Nibbler()
{
    delete _snake;
}

Nibbler::Nibbler(Nibbler const &cpy)
{
    *this = cpy;
}

Nibbler& Nibbler::operator=(Nibbler const &cpy)
{
    if (this == &cpy)
        return (*this);
    _map_height = cpy._map_height;
    _map_width = cpy._map_width;
    _snake = cpy._snake;
    _foods = cpy._foods;
    _obstacles = cpy._obstacles;
    _interface = cpy._interface;
    _score = cpy._score;
    _gameover = cpy._gameover;
    return (*this);
}

void Nibbler::setMapHeight(int map_height)
{
    this->_map_height = map_height;
}

void Nibbler::setMapWidth(int map_width)
{
    this->_map_width = map_width;
}

void Nibbler::setSnake(Snake *snake)
{
    this->_snake = snake;
}

void Nibbler::setFoods(std::vector<Food> foods)
{
    this->_foods = foods;
}

void Nibbler::setObstacles(std::vector<Obstacle> obstacles)
{
    this->_obstacles = obstacles;
}

void Nibbler::setInterface(library_t interface)
{
    this->_interface = interface;
}

void Nibbler::setScore(int score)
{
    this->_score = score;
}

void Nibbler::setGameover(int gameover)
{
    this->_gameover = gameover;
}

int Nibbler::getMapHeight(void) const
{
    return(this->_map_height);
}

int Nibbler::getMapWidth(void) const
{
    return(this->_map_width);
}

Snake *Nibbler::getSnake(void) const
{
    return(this->_snake);
}

std::vector<Food> Nibbler::getFoods(void) const
{
    return(this->_foods);
}

std::vector<Obstacle> Nibbler::getObstacles(void) const
{
    return(this->_obstacles);
}

library_t Nibbler::getInterface(void) const
{
    return(this->_interface);
}

int Nibbler::getScore(void) const
{
    return(this->_score);
}

int Nibbler::getGameover(void) const
{
    return(this->_gameover);
}

bool Nibbler::isFood(int y, int x)
{
    for (std::vector<Food>::iterator it = _foods.begin(); it != _foods.end(); it++)
    {
        if (it->getX() == x && it->getY() == y)
        {
            return (true);
        }
    }
    return (false);
}

bool Nibbler::isSnake(int y, int x)
{
    if (_snake->getX() == x && _snake->getY() == y)
        return (true);
    std::vector<SnakeBodyPart> body = _snake->getBody();
    for (std::vector<SnakeBodyPart>::iterator it = body.begin(); it != body.end(); it++)
    {
        if (it->getX() == x && it->getY() == y)
        {
            return (true);
        }
    }
    return (false);
}

bool Nibbler::isWall(int y, int x)
{
    if (x < 0 || x >= _map_width || y < 0 || y >= _map_height)
        return (1);
    return (0);
}

bool Nibbler::isObstacle(int y, int x)
{
    for (std::vector<Obstacle>::iterator it = _obstacles.begin(); it != _obstacles.end(); it++)
    {
        if (it->getX() == x && it->getY() == y)
        {
            return (true);
        }
    }
    return (false);
}

void Nibbler::moveSnake(void)
{
    std::pair<int, int> next_pos = _snake->getNextPos();
    if (this->isSnake(next_pos.first, next_pos.second)
        || this->isObstacle(next_pos.first, next_pos.second)
        || this->isWall(next_pos.first, next_pos.second))
    {
        std::vector<SnakeBodyPart> body = _snake->getBody();
        SnakeBodyPart tail = body.back();
        if (next_pos.first != tail.getY() || next_pos.second != tail.getX())
        {
            _gameover++;
            return;
        }
    }
    _gameover = 0;
    _snake->move();
    _score -= SCORE_REMOVED_EVERY_TURN;
    if (_score < 0)
        _score = 0;
}

std::pair<int, int> Nibbler::generateRandomPosition(void)
{
    std::vector<std::pair<int, int> > possible_squares;
    for (int y = 0; y < _map_height; y++)
    {
        for (int x = 0; x < _map_width; x++)
        {
            if (!this->isSnake(y, x) && !this->isFood(y, x) && !this->isObstacle(y, x))
                possible_squares.push_back(std::make_pair(y, x));
        }
    }
    int random = rand() % possible_squares.size();
    return (possible_squares[random]);
}

void Nibbler::generateRandomFood(food_type_t type)
{
    std::pair<int, int> random_position = generateRandomPosition();
    _foods.push_back(Food(random_position.first, random_position.second, type));
}

food_type_t Nibbler::getFoodType(int y, int x)
{
    for (std::vector<Food>::iterator it = _foods.begin(); it != _foods.end(); it++)
    {
        if (it->getX() == x && it->getY() == y)
        {
            return (it->getType());
        }
    }
    return (food_type_t::NORMAL); // should never be used
}

void Nibbler::removeFood(int y, int x)
{
    for (std::vector<Food>::iterator it = _foods.begin(); it != _foods.end(); it++)
    {
        if (it->getX() == x && it->getY() == y)
        {
            _foods.erase(it);
            break;
        }
    }
}

void Nibbler::removeMalusFood(void)
{
    for (std::vector<Food>::iterator it = _foods.begin(); it != _foods.end(); it++)
    {
        if (it->getType() == food_type_t::MALUS)
        {
            _foods.erase(it);
            break;
        }
    }
}

void Nibbler::generateRandomObstacle(void)
{
    std::pair<int, int> random_position = generateRandomPosition();
    _obstacles.push_back(Obstacle(random_position.first, random_position.second));
}
