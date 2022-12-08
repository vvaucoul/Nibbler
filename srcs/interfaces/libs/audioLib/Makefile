# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/25 12:16:00 by vvaucoul          #+#    #+#              #
#    Updated: 2022/11/28 13:09:46 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../dependencies/rules.mk
include ../dependencies/colors.mk

INCLUDES			= 	-I../../ \
						-I $(HOME_PATH)/libs/miniaudio/

LIB_FLAGS			=	-L $(HOME_PATH)/libs/miniaudio/ \
						-ldl -lm -lpthread

NAME				=	libaudio.so
SRCS				=	libaudio.cpp

OBJS				=	$(SRCS:.cpp=.o)

%.o: %.cpp
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) : $(_LWHITE)$<$(_END)$(_DIM) --------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" "LibAudio"
	@$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(SHARED_LIB_FLAGS) -o $(NAME) $(OBJS) $(LIB_FLAGS)
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) $(_LWHITE)Compiled !$(_END)$(_DIM) ---------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re