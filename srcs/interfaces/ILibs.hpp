/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ILibs.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:17:12 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/12/01 19:11:17 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ILIBS_HPP
#define ILIBS_HPP

#include <string>
#include <vector>
#include <map>

typedef enum e_input
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    QUIT,
    LIB1,
    LIB2,
    LIB3
} input_t;

typedef struct s_lib_parameter
{
    uint32_t width;
    uint32_t height;
    uint32_t fps;

    void (*inputHandler)(input_t const &);
} lib_parameter_t;

typedef enum e_food_type
{
    NORMAL,
    BONUS,
    MALUS
} food_type_t;

typedef struct s_food
{
    int x;
    int y;
    food_type_t type;
} food_t;

typedef struct s_game
{
    // pair are y, x (height, width)
    std::vector<std::pair<int, int>> snake; //H -> B1 -> B2...
    std::vector<food_t> foods;
    std::vector<std::pair<int, int>> obstacles;
    input_t snake_direction;
    int score;
} game_t;

class ILibs
{
protected:
    std::map<uint32_t, input_t> _inputs;
    lib_parameter_t _parameter;

    virtual void initInputs(void) = 0;
    virtual void libSleep(void) = 0;

public:
    virtual ~ILibs(void) = default;

    virtual void update(game_t const &) = 0;
};

#endif /* ILIBS_HPP */