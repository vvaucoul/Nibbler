# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compil.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 17:14:00 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 18:19:41 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

g++ -shared -fPIC -o libsquarepp.so square.cpp
g++ main.cpp -ldl
./a.out ./libsquarepp.so
rm libsquarepp.so a.out