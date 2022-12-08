/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ai.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:44:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/02 12:59:55 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ai.hpp"

AI::AI()
{
}

AI::~AI()
{
}

static int getDistance(int x1, int y1, int x2, int y2)
{
    return (std::abs(x1 - x2) + std::abs(y1 - y2));
}

std::vector<std::pair<uint32_t, uint32_t>> AI::getPathToLocation(lib_parameter_t const &parameter, std::vector<std::pair<int, int>> const &obstacles)
{
    std::vector<std::pair<uint32_t, uint32_t>> path;
    std::pair<uint32_t, uint32_t> currentLocation = std::make_pair(parameter.width / 2, parameter.height / 2);
    std::pair<uint32_t, uint32_t> targetLocation = std::make_pair(parameter.width / 2, parameter.height / 2);

    while (currentLocation != targetLocation)
    {
        int distance = getDistance(currentLocation.first, currentLocation.second, targetLocation.first, targetLocation.second);
        int distanceUp = getDistance(currentLocation.first, currentLocation.second - 1, targetLocation.first, targetLocation.second);
        int distanceDown = getDistance(currentLocation.first, currentLocation.second + 1, targetLocation.first, targetLocation.second);
        int distanceLeft = getDistance(currentLocation.first - 1, currentLocation.second, targetLocation.first, targetLocation.second);
        int distanceRight = getDistance(currentLocation.first + 1, currentLocation.second, targetLocation.first, targetLocation.second);

        if (distanceUp < distance)
        {
            currentLocation.second -= 1;
            path.push_back(std::make_pair(currentLocation.first, currentLocation.second));
        }
        else if (distanceDown < distance)
        {
            currentLocation.second += 1;
            path.push_back(std::make_pair(currentLocation.first, currentLocation.second));
        }
        else if (distanceLeft < distance)
        {
            currentLocation.first -= 1;
            path.push_back(std::make_pair(currentLocation.first, currentLocation.second));
        }
        else if (distanceRight < distance)
        {
            currentLocation.first += 1;
            path.push_back(std::make_pair(currentLocation.first, currentLocation.second));
        }
    }
    return (path);
}

std::pair<uint32_t, uint32_t> AI::BackTrackToLocation(lib_parameter_t const &parameter, game_t const &game)
{
    std::pair<uint32_t, uint32_t> location = std::make_pair(0, 0);
    int distance = 0;
    std::vector<std::pair<uint32_t, uint32_t>> current_path;

    std::vector<food_t> foods = game.foods;
    std::vector<std::pair<int, int>> obstacles = game.obstacles;

    for (auto &food : foods)
    {
        current_path = getPathToLocation(parameter, obstacles);
        if (current_path.size() < distance || distance == 0)
        {
            distance = current_path.size();
            location = std::make_pair(food.x, food.y);
        }
    }
    
    for (auto &loc : current_path)
    {
        std::cout << loc.first << " " << loc.second << std::endl;
    }

    // while (1);

    return (location);
}

input_t AI::findBestMove(lib_parameter_t const &parameter, game_t const &game)
{
    std::pair<uint32_t, uint32_t> location = BackTrackToLocation(parameter, game);
    std::pair<uint32_t, uint32_t> snakeLocation = game.snake[0];

    if (location.first == 0 && location.second == 0)
        return (input_t::NONE);
    if (location.first > snakeLocation.second)
        return (input_t::RIGHT);
    if (location.first < snakeLocation.second)
        return (input_t::LEFT);
    if (location.second > snakeLocation.first)
        return (input_t::DOWN);
    if (location.second < snakeLocation.first)
        return (input_t::UP);
    return (input_t::NONE);
}