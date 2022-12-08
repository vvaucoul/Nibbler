# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_miniaudio.sh                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 12:14:08 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:42:15 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# COLORS
IWHITE='\033[1;37m'
IRED='\033[0;91m'
IGREEN='\033[0;92m'
IYELLOW='\033[0;93m'
ENDC='\033[0m'

# Install miniaudio
printf "$IYELLOW%s$ENDC\n" "Installing MINIAUDIO..."
wget https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h -P ./tmp/miniaudio/miniaudio.h > /dev/null 2>&1
mkdir -p ~/libs/miniaudio/ > /dev/null 2>&1
cp ./tmp/miniaudio/miniaudio.h/miniaudio.h ~/libs/miniaudio/miniaudio.h > /dev/null 2>&1
printf "$IGREEN%s$ENDC\n" "MINIAUDIO Installed !"
