# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compil.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 17:14:00 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 18:19:36 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

gcc -shared -fPIC -o libsquare.so square.c
g++ main.cpp  -ldl
./a.out ./libsquare.so
rm libsquare.so a.out