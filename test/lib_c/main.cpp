/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:10:06 by vvaucoul          #+#    #+#             */
/*   Updated: 2022/11/22 17:23:10 by vvaucoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

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
        int (*square)(int) = (int (*)(int))dlsym(handler, "square");
        printf("3 * 3 = %d\n", square(3));
        dlclose(handler);
    }
    return (0);
}