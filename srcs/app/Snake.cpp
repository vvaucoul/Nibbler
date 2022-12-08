/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:35:49 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:59:17 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake()
:   _y(0),
    _x(0),
    _direction(RIGHT),
    _next_direction(RIGHT),
    _size(0)
{}

Snake::Snake(int y, int x, input_t direction, int size)
:   _y(y),
    _x(x),
    _direction(direction),
    _next_direction(direction),
    _size(size)
{
    for (int i = 1; i < size; i++)
    {
        if (direction == RIGHT)
            _body.push_back(SnakeBodyPart(y, x - i));
        else if (direction == LEFT)
            _body.push_back(SnakeBodyPart(y, x + i));
        else if (direction == UP)
            _body.push_back(SnakeBodyPart(y + i, x));
        else if (direction == DOWN)
            _body.push_back(SnakeBodyPart(y - i, x));
    }
}

Snake::~Snake()
{
    _body.clear();
}

Snake::Snake(Snake const &cpy)
{
    *this = cpy;
}

Snake& Snake::operator=(Snake const &cpy)
{
    if (this == &cpy)
        return (*this);
    setY(cpy.getY());
    setX(cpy.getX());
    setDirection(cpy.getDirection());
    setSize(cpy.getSize());
    return (*this);
}

void Snake::setY(int y)
{
    this->_y = y;
}

void Snake::setX(int x)
{
    this->_x = x;
}

void Snake::setDirection(input_t direction)
{
    this->_direction = direction;
}

void Snake::setSize(int size)
{
    this->_size = size;
}

void Snake::setBody(std::vector<SnakeBodyPart> body)
{
    this->_body = body;
}

int Snake::getY(void) const
{
    return(this->_y);
}

int Snake::getX(void) const
{
    return(this->_x);
}

input_t Snake::getDirection(void) const
{
    return(this->_direction);
}

int Snake::getSize(void) const
{
    return(this->_size);
}

std::vector<SnakeBodyPart> Snake::getBody(void) const
{
    return(this->_body);
}

void Snake::changeDirection(input_t direction)
{
    if (direction == UP && _direction != DOWN
        || direction == DOWN && _direction != UP
        || direction == LEFT && _direction != RIGHT
        || direction == RIGHT && _direction != LEFT)
        _next_direction = direction;
}

std::pair<int, int> Snake::getNextPos(void) const
{
    std::pair<int, int> pos;

    pos.first = _y;
    pos.second = _x;
    if (_next_direction == UP)
        pos.first--;
    if (_next_direction == DOWN)
        pos.first++;
    if (_next_direction == LEFT)
        pos.second--;
    if (_next_direction == RIGHT)
        pos.second++;
    return (pos);
}

void Snake::move(void)
{
    _body.insert(_body.begin(), SnakeBodyPart(_y, _x));
    if (_next_direction == UP)
        _y--;
    if (_next_direction == DOWN)
        _y++;
    if (_next_direction == LEFT)
        _x--;
    if (_next_direction == RIGHT)
        _x++;
    _direction = _next_direction;
    while (_body.size() >= _size)
        _body.pop_back();
}

void Snake::grow(int amount)
{
    _size += amount;
}
