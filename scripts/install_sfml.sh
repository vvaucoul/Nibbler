# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_sfml.sh                                    :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:54:40 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:48:16 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# COLORS
IWHITE='\033[1;37m'
IRED='\033[0;91m'
IGREEN='\033[0;92m'
IYELLOW='\033[0;93m'
ENDC='\033[0m'

# Install SFML
printf "$IYELLOW%s$ENDC\n" "Installing SFML..."
wget https://www.sfml-dev.org/files/SFML-2.5.1-linux-gcc-64-bit.tar.gz -P ./tmp/ > /dev/null 2>&1
tar -xvf ./tmp/SFML-2.5.1-linux-gcc-64-bit.tar.gz -C ./tmp/ > /dev/null 2>&1
cd ./tmp/SFML-2.5.1/ > /dev/null 2>&1
mkdir -p ~/libs/SFML-2.5.1/ > /dev/null 2>&1
cp -r ./* ~/libs/SFML-2.5.1/ > /dev/null 2>&1

printf "$IGREEN%s$ENDC\n" "SFML Installed !"
echo ""

LOGNAME=$(whoami)

printf "⚠️ $IWHITE%s$ENDC\n" "Run the following command to add the library path. ⚠️"
printf "$IGREEN%s$ENDC\n" "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/mnt/nfs/homes/$LOGNAME/libs/SFML-2.5.1/lib/"
echo ""