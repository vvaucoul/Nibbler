/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Food.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:17:09 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:54:28 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FOOD_HPP
# define FOOD_HPP

#include "ILibs.hpp"

class Food
{
    private:
        int _y;
        int _x;
        food_type_t _type;
    
    public:
        Food();
        Food(int y, int x, food_type_t type);
        ~Food();
        Food(Food const &cpy);
        Food &operator=(Food const &cpy);

        void setY(int y);
        void setX(int x);
        void setType(food_type_t type);

        int getY(void) const;
        int getX(void) const;
        food_type_t getType(void) const;
        
};

# endif
