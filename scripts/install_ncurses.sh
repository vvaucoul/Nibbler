# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_ncurses.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:48:36 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:44:55 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# COLORS
IWHITE='\033[1;37m'
IRED='\033[0;91m'
IGREEN='\033[0;92m'
IYELLOW='\033[0;93m'
ENDC='\033[0m'

# Install ncurses
printf "$IYELLOW%s$ENDC\n" "Installing NCURSES..."
wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.3.tar.gz -P ./tmp/ > /dev/null 2>&1
tar -xvf ./tmp/ncurses-6.3.tar.gz -C ./tmp/ > /dev/null 2>&1
cd ./tmp/ncurses-6.3/  > /dev/null 2>&1 && ./configure > /dev/null 2>&1 && make > /dev/null 2>&1
printf "$IGREEN%s$ENDC\n" "NCURSES Installed !"
echo ""