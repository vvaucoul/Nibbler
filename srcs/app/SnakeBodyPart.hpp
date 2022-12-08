/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeBodyPart.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:16:54 by mle-faou          #+#    #+#             */
/*   Updated: 2022/12/02 13:56:56 by mle-faou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef SNAKEBODYPART_HPP
# define SNAKEBODYPART_HPP

class SnakeBodyPart
{
    private:
        int _y;
        int _x;
    
    public:
        SnakeBodyPart();
        SnakeBodyPart(int y, int x);
        ~SnakeBodyPart();
        SnakeBodyPart(SnakeBodyPart const &cpy);
        SnakeBodyPart &operator=(SnakeBodyPart const &cpy);

        void setY(int y);
        void setX(int x);

        int getY(void) const;
        int getX(void) const;
};

# endif