/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeBodyPart.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:17:52 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:57:37 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeBodyPart.hpp"

SnakeBodyPart::SnakeBodyPart()
:   _y(0),
    _x(0)
{}

SnakeBodyPart::SnakeBodyPart(int y, int x)
:   _y(y),
    _x(x)
{}

SnakeBodyPart::~SnakeBodyPart()
{}

SnakeBodyPart::SnakeBodyPart(SnakeBodyPart const &cpy)
{
    *this = cpy;
}

SnakeBodyPart& SnakeBodyPart::operator=(SnakeBodyPart const &cpy)
{
    if (this == &cpy)
        return (*this);
    setY(cpy.getY());
    setX(cpy.getX());
    return (*this);
}

void SnakeBodyPart::setY(int y)
{
    this->_y = y;
}

void SnakeBodyPart::setX(int x)
{
    this->_x = x;
}

int SnakeBodyPart::getY(void) const
{
    return (this->_y);
}

int SnakeBodyPart::getX(void) const
{
    return (this->_x);
}
