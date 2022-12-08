# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 23:45:30 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 14:38:16 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../dependencies/rules.mk
include ../../dependencies/colors.mk

# clang++-12 -o test -fPIC libsfml.cpp -shared -I ../../../../tmp/SFML-2.5.1/include -L ../../../../tmp/SFML-2.5.1/lib/ -lsfml-graphics -lsfml-window -lsfml-system

INCLUDES		= 	-I../../ \
					-I $(HOME_PATH)/libs/SFML-2.5.1/include \

LIB_FLAGS		=	-L $(HOME_PATH)/libs/SFML-2.5.1/lib \
					-lsfml-graphics \
					-lsfml-window \
					-lsfml-system \
					-lsfml-audio

NAME = libsfml.so
SRCS = libsfml.cpp

OBJS = $(SRCS:.cpp=.o)
DEPENDS = $(SRCS:.cpp=.d)

%.o: %.cpp
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) : $(_LWHITE)$<$(_END)$(_DIM) ----------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" "LibSFML"
	@$(CXX) $(CFLAGS) $(INCLUDES) -MD -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) -o $(NAME) $(CFLAGS) $(OBJS) $(SHARED_LIB_FLAGS) $(LIB_FLAGS)
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) $(_LWHITE)Compiled !$(_END)$(_DIM) ----------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" $(NAME)

clean:
	@rm -rf $(OBJS) $(DEPENDS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPENDS)