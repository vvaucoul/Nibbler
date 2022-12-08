# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 12:16:44 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 17:38:37 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include mk-files/colors.mk

CXX = clang++-12
INCLUDES = -I includes/ -I srcs/ -I srcs/interfaces/ -I srcs/interfaces/libs/
CAFLAGS = -g3 -std=c++17 -ldl
CXXFLAGS = $(CAFLAGS) $(INCLUDES) -Wall -Wextra -Werror # -fsanitize=leak
NAME = nibbler

SRCS_DIR = srcs/
EXLUDE_DIR = srcs/interfaces/libs
SRCS = $(shell find $(SRCS_DIR) -name "*.cpp" | grep -v $(EXLUDE_DIR))
OBJS = $(SRCS:.cpp=.o)
SCRIPT_DIR = scripts/
LIB_DIR = libs/
LIBS_DEPENDENCIES_DIR = ./tmp/

LIBS_DIR = srcs/interfaces/libs/

%.o: %.cpp
	@printf "$(_LWHITE)- $(_LGREEN)%s$(_END) : $(_LWHITE)$<$(_END)\n" "Nibbler"
	@$(CXX) $(CFLAGS) $(INCLUDES) -g3 -c $< -o $@

all: ascii libs $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) -g3 $(OBJS) -o $(NAME)
	@printf "\n$(_LWHITE)- $(_LCYAN)%s$(_END) $(_LWHITE)Compiled !$(_END)$(_DIM) -------------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" Nibbler

clean:
	@rm -rf $(OBJS)
	@make -s -C $(LIBS_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIB_DIR)
	@make -s -C $(LIBS_DIR) fclean

re: fclean all

ilibs:
	@make -s -C $(LIBS_DIR)
	@mkdir -p $(LIB_DIR)
	@cp $(LIBS_DIR)/graphicLibs/libncurses/libncurses.so ./$(LIB_DIR)/libncurses.so
	@cp $(LIBS_DIR)/graphicLibs/libsfml/libsfml.so ./$(LIB_DIR)/libsfml.so
	@cp $(LIBS_DIR)/graphicLibs/libopengl/libopengl.so ./$(LIB_DIR)/libopengl.so
	@cp $(LIBS_DIR)/audioLib/libaudio.so ./$(LIB_DIR)/libaudio.so
	@printf "\n"

libs: $(LIBS_DEPENDENCIES_DIR) ilibs

$(LIBS_DEPENDENCIES_DIR): 
	@sh $(SCRIPT_DIR)/install_libs.sh && make -s -C . install-libs

install-libs:
	@rm -rf ./tmp > /dev/null 2>&1
	@sh $(SCRIPT_DIR)install_ncurses.sh
	@sh $(SCRIPT_DIR)install_sfml.sh
	@sh $(SCRIPT_DIR)install_opengl.sh
	@sh $(SCRIPT_DIR)install_miniaudio.sh

uninstall-libs:
	@rm -rf tmp

ascii:
	@printf "$(_LGREEN)  _   _ _____ ____  ____  _      ______ _____  	\n$(_END)"
	@printf "$(_LGREEN) | \ | |_   _|  _ \|  _ \| |    |  ____|  __ \ 	\n$(_END)"
	@printf "$(_LGREEN) |  \| | | | | |_) | |_) | |    | |__  | |__) |	\n$(_END)"
	@printf "$(_LGREEN) | . \ | | | |  _ <|  _ <| |    |  __| |  _  / 	\n$(_END)"
	@printf "$(_LGREEN) | |\  |_| |_| |_) | |_) | |____| |____| | \ \ 	\n$(_END)"
	@printf "$(_LGREEN) |_| \_|_____|____/|____/|______|______|_|  \_\ 	\n\n$(_END)"
                                        
.PHONY: all clean fclean re install-libs uninstall-libs ilibs