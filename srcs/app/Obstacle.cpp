/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:49:54 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:56:14 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Obstacle.hpp"

Obstacle::Obstacle()
:   _y(0),
    _x(0)
{}

Obstacle::Obstacle(int y, int x)
:   _y(y),
    _x(x)
{}

Obstacle::~Obstacle()
{}

Obstacle::Obstacle(Obstacle const &cpy)
{
    *this = cpy;
}

Obstacle& Obstacle::operator=(Obstacle const &cpy)
{
    if (this == &cpy)
        return (*this);
    setY(cpy.getY());
    setX(cpy.getX());
    return (*this);
}

void Obstacle::setY(int y)
{
    _y = y;
}

void Obstacle::setX(int x)
{
    _x = x;
}

int Obstacle::getY() const
{
    return (_y);
}

int Obstacle::getX() const
{
    return (_x);
}
