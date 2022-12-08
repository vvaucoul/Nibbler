# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    install_opengl.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:58:23 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:45:26 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

# COLORS
IWHITE='\033[1;37m'
IRED='\033[0;91m'
IGREEN='\033[0;92m'
IYELLOW='\033[0;93m'
ENDC='\033[0m'

# Install OpenGL
printf "$IYELLOW%s$ENDC\n" "Installing OPENGL(GLFW)..."
wget https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip -P ./tmp/ > /dev/null 2>&1
unzip ./tmp/glfw-3.3.8.zip -d ./tmp/ > /dev/null 2>&1
cd ./tmp/glfw-3.3.8/ > /dev/null 2>&1
cmake . > /dev/null 2>&1
make > /dev/null 2>&1
cp -r . ~/libs/glfw-3.3.8/ > /dev/null 2>&1
cd ../.. > /dev/null 2>&1
printf "$IGREEN%s$ENDC\n" "OPENGL(GLFW) Installed !"
echo ""

# echo "Installing GLEW..."
# wget https://altushost-swe.dl.sourceforge.net/project/glew/glew/2.1.0/glew-2.1.0.zip -P ./tmp/
# unzip ./tmp/glew-2.1.0.zip -d ./tmp/
# cd ./tmp/glew-2.1.0/
# make
# cp -r . ~/libs/glew-2.1.0/
# cd ../..

# echo "Installing GLUT..."
# wget https://github.com/FreeGLUTProject/freeglut/releases/download/v3.4.0/freeglut-3.4.0.tar.gz -P ./tmp/
# tar -xvf ./tmp/freeglut-3.4.0.tar.gz -C ./tmp/
# cd ./tmp/freeglut-3.4.0/
# cmake .
# make
# cp -r . ~/libs/freeglut-3.4.0/
# cd ../..