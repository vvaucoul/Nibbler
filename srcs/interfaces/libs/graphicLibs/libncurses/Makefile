# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:12:48 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/01 19:29:58 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../dependencies/rules.mk
include ../../dependencies/colors.mk

INCLUDES			= 	-I../../

LIB_FLAGS = -lncurses

LIB_NCURSES_DIR = ../../../../tmp/ncurses-6.3/lib/

NAME = libncurses.so
SRCS = libncurses.cpp

OBJS = $(SRCS:.cpp=.o)
DEPENDS = $(SRCS:.cpp=.d)

%.o: %.cpp
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) : $(_LWHITE)$<$(_END)$(_DIM) ----- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" "LibNcurses"
	@$(CXX) $(CFLAGS) $(INCLUDES) -MD -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(SHARED_LIB_FLAGS) -o $(NAME) $(OBJS) -L$(LIB_NCURSES_DIR)/libncurses.a $(LIB_FLAGS) $(CFLAGS)
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) $(_LWHITE)Compiled !$(_END)$(_DIM) -------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" $(NAME)

clean:
	@rm -rf $(OBJS) $(DEPENDS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPENDS)