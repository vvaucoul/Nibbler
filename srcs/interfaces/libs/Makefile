# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:24:02 by vvaucoul          #+#    #+#              #
#    Updated: 2022/11/29 16:44:41 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRAPHICS_LIB_DIR = graphicLibs
AUDIO_LIB_DIR = audioLib

all:
	@make -C $(GRAPHICS_LIB_DIR)/libncurses
	@make -C $(GRAPHICS_LIB_DIR)/libsfml
	@make -C $(GRAPHICS_LIB_DIR)/libopengl
	@make -C $(AUDIO_LIB_DIR)/

clean:
	@make clean -C $(GRAPHICS_LIB_DIR)/libncurses
	@make clean -C $(GRAPHICS_LIB_DIR)/libsfml
	@make clean -C $(GRAPHICS_LIB_DIR)/libopengl
	@make clean -C $(AUDIO_LIB_DIR)/

fclean:
	@make fclean -C $(GRAPHICS_LIB_DIR)/libncurses
	@make fclean -C $(GRAPHICS_LIB_DIR)/libsfml
	@make fclean -C $(GRAPHICS_LIB_DIR)/libopengl
	@make fclean -C $(AUDIO_LIB_DIR)/

re: fclean all

.PHONY: all clean fclean re