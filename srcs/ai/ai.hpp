/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:44:28 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/02 12:58:26 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AI_HPP
#define AI_HPP

#include <ILibs.hpp>
#include <iostream>

class AI
{
private:
public:
    AI();
    ~AI();

    input_t findBestMove(lib_parameter_t const &parameter, game_t const &game);
    std::pair<uint32_t, uint32_t> BackTrackToLocation(lib_parameter_t const &parameter, game_t const &game);
    std::vector<std::pair<uint32_t, uint32_t>> getPathToLocation(lib_parameter_t const &parameter, std::vector<std::pair<int, int>> const &obstacles);
};

#endif /* AI_HPP */