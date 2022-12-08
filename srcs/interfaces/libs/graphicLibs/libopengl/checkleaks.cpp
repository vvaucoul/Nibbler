/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkleaks.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 15:40:49 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/29 17:02:13 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libopengl.hpp"

int main()
{
    lib_parameter_t param;

    param.width = 20;
    param.height = 20;
    param.fps = 10;
    param.inputHandler = nullptr;

    LibOpenGL *lib = new LibOpenGL(param);
    delete lib;
    return (0);
}