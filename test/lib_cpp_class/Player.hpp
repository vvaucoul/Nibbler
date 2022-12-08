/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:26:31 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/22 17:28:37 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "IPlayer.hpp"
#include <iostream>

class Player : public IPlayer
{
private:
    std::string _name;
    uint32_t _score;
    
    Player(void);

    public:
    Player(std::string name);
    ~Player(void);

    std::string getName(void);
    uint32_t getScore(void);
};

extern "C"
{
    Player *createPlayer(std::string name);
    void deletePlayer(Player *player);
}

#endif /* PLAYER_HPP */