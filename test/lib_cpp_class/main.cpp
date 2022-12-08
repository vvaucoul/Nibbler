/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:10:06 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/22 17:34:47 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "Player.hpp"

int main(int argc, char **argv)
{
    void *handler = dlopen(argv[1], RTLD_LAZY | RTLD_LOCAL);

    if (handler == NULL)
    {
        printf("Error: %s\n", dlerror());
        return (1);
    }
    else
    {
        IPlayer *(*createPlayer)(std::string);

        createPlayer = (IPlayer * (*)(std::string)) dlsym(handler, "createPlayer");

        if (!createPlayer)
        {
            printf("Error: %s\n", dlerror());
            return (1);
        }
        IPlayer *player = createPlayer("test");

        std::cout << "Name: " << player->getName() << std::endl;
        dlclose(handler);
    }
    return (0);
}