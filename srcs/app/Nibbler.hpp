/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nibbler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 12:19:13 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/06 18:16:09 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef NIBBLER_HPP
# define NIBBLER_HPP

#include <iostream>
#include <string>
#include <unistd.h>

#include <vector>

#include "Snake.hpp"
#include "Food.hpp"
#include "Obstacle.hpp"

#include "wrapper.hpp"

# define MIN_MAP_HEIGHT 10
# define MAX_MAP_HEIGHT 42
# define MIN_MAP_WIDTH 10
# define MAX_MAP_WIDTH 42

# define INTERFACE1 "ncurses"
# define INTERFACE2 "sfml"
# define INTERFACE3 "opengl"

# define INITIAL_DIRECTION RIGHT
# define INITIAL_SIZE 4
# define INITIAL_SCORE 100

// make obstacles spawn away from snake
// scoreboard with save in file

# define MAX_FOODS 5
# define CHANCE_TO_SPAWN_FOOD 5 // 1 chance out of CHANCE_TO_SPAWN_FOOD to spawn a food each time the snake moves
# define CHANCE_TO_SPAWN_BONUS 5 // 1 chance out of CHANCE_TO_SPAWN_BONUS to spawn a bonus food each time the snake moves
# define CHANCE_TO_SPAWN_MALUS 3 // 1 chance out of CHANCE_TO_SPAWN_MALUS to spawn a malus food each time the snake moves

# define CHANCE_TO_DESPAWN_MALUS_FOOD 100 // 1 chance out of CHANCE_TO_DESPAWN_FOOD to despawn a malusfood each time the snake moves

# define INITIAL_OBSTACLES 3
# define CHANCE_TO_SPAWN_OBSTACLE 1 // 1 chance out of CHANCE_TO_SPAWN_OBSTACLE to spawn an obstacle each time the snake eats a food

# define FOOD_SCORE 100
# define BONUS_FOOD_SCORE 300
# define MALUS_FOOD_SCORE -100
# define SCORE_REMOVED_EVERY_TURN 1
# define PITY_AMOUNT 2 // time the snake is allowed to hit a wall before gameover

// 0:0 top left

class Nibbler
{
    private:
        int _map_height;
        int _map_width;
        Snake *_snake;
        std::vector<Food> _foods;
        std::vector<Obstacle> _obstacles;
        library_t _interface;
        int _score;
        int _gameover;

    public:
        Nibbler();
        Nibbler(int map_height, int map_width, std::string interface);
        ~Nibbler();
        Nibbler(Nibbler const &cpy);
        Nibbler &operator=(Nibbler const &cpy);

        void setMapHeight(int map_height);
        void setMapWidth(int map_width);
        void setSnake(Snake *snake);
        void setFoods(std::vector<Food> foods);
        void setObstacles(std::vector<Obstacle> obstacles);
        void setInterface(library_t interface);
        void setScore(int score);
        void setGameover(int gameover);

        int getMapHeight(void) const;
        int getMapWidth(void) const;
        Snake *getSnake(void) const;
        std::vector<Food> getFoods(void) const;
        std::vector<Obstacle> getObstacles(void) const;
        library_t getInterface(void) const;
        int getScore(void) const;
        int getGameover(void) const;

        bool isFood(int y, int x);
        bool isSnake(int y, int x);
        bool isWall(int y, int x);
        bool isObstacle(int y, int x);

        void moveSnake(void);
        std::pair<int, int> generateRandomPosition(void);
        void generateRandomFood(food_type_t type);
        food_type_t getFoodType(int y, int x);
        void removeFood(int y, int x);
        void removeMalusFood(void);
        void generateRandomObstacle(void);

};

# endif
