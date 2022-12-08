/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:15:24 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:59:22 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SNAKE_HPP
# define SNAKE_HPP

#include <vector>
#include <string>

#include "ILibs.hpp"
#include "SnakeBodyPart.hpp"

class Snake
{
    private:
        int _y;
        int _x;
        input_t _direction;
        input_t _next_direction;
        int _size;
        std::vector<SnakeBodyPart> _body;

    public:
        Snake();
        Snake(int y, int x, input_t direction, int size);
        ~Snake();
        Snake(Snake const &cpy);
        Snake &operator=(Snake const &cpy);

        void setY(int y);
        void setX(int x);
        void setDirection(input_t direction);
        void setSize(int size);
        void setBody(std::vector<SnakeBodyPart> body);

        int getY(void) const;
        int getX(void) const;
        input_t getDirection(void) const;
        int getSize(void) const;
        std::vector<SnakeBodyPart> getBody(void) const;

        void changeDirection(input_t direction);
        std::pair<int, int> getNextPos(void) const;
        void move(void);
        void grow(int amount);

};

# endif
