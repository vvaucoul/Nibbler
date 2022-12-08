/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IPlayer.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:26:15 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/22 19:24:05 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IPLAYER_HPP
#define IPLAYER_HPP

#include <string>

class IPlayer
{
public:
    virtual ~IPlayer(void) = default;
    virtual std::string getName(void) = 0;
    virtual uint32_t getScore(void) = 0;
};

#endif /* IPLAYER_HPP */