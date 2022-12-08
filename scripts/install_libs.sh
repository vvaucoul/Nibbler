# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_libs.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/23 11:22:30 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:38:08 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

ls tmp > /dev/null 2>&1
if [ $? -ne 0 ]; then
    echo "Installing libs..."
    exit 0
elif [ $? -eq 0 ]; then
    echo "Libs already installed"
    exit 1
fi