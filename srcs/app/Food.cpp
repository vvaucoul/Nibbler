/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 14:40:53 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:56:00 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Food.hpp"

Food::Food()
:   _y(0),
    _x(0),
    _type(NORMAL)
{}

Food::Food(int y, int x, food_type_t type)
:   _y(y),
    _x(x),
    _type(type)
{}

Food::~Food()
{}

Food::Food(Food const &cpy)
{
    *this = cpy;
}

Food& Food::operator=(Food const &cpy)
{
    if (this == &cpy)
        return (*this);
    setY(cpy.getY());
    setX(cpy.getX());
    setType(cpy.getType());
    return (*this);
}

void Food::setY(int y)
{
    this->_y = y;
}

void Food::setX(int x)
{
    this->_x = x;
}

void Food::setType(food_type_t type)
{
    this->_type = type;
}

int Food::getY(void) const
{
    return (this->_y);
}

int Food::getX(void) const
{
    return (this->_x);
}

food_type_t Food::getType(void) const
{
    return (this->_type);
}
