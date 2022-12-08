/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:27:41 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/22 18:41:57 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player(std::string name) : _name(name), _score(0)
{
    return;
}

Player::~Player(void)
{
    return;
}

std::string Player::getName(void)
{
    return (_name);
}

uint32_t Player::getScore(void)
{
    return (_score);
}

Player *createPlayer(std::string name)
{
    return (new Player(name));
}

void deletePlayer(Player *player)
{
    delete player;
}