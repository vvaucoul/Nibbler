/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkleaks.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/28 15:42:14 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsfml.hpp"

int main()
{
    lib_parameter_t param;

    param.width = 20;
    param.height = 20;
    param.fps = 10;
    param.inputHandler = nullptr;

    LibSFML *lib = new LibSFML(param);
    delete lib;
    return (0);
}