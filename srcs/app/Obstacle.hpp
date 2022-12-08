/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 20:43:00 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:55:24 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

class Obstacle
{
    private:
        int _y;
        int _x;

    public:
        Obstacle();
        Obstacle(int y, int x);
        ~Obstacle();
        Obstacle(Obstacle const &cpy);
        Obstacle &operator=(Obstacle const &cpy);

        void setY(int y);
        void setX(int x);

        int getY() const;
        int getX() const;

};

# endif