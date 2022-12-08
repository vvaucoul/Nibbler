# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-faou <mle-faou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:29:35 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/06 14:35:43 by mle-faou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ../../dependencies/rules.mk
include ../../dependencies/colors.mk

NAME = libopengl.so

LIB_GLFW_DIR = glfw-3.3.8
LIB_GLEW_DIR = glew-2.1.0
LIB_FREEGLUT_DIR = freeglut-3.4.0

LIB_FLAGS = -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lglut  #-lglfw3 -lGLEW -lGL -lGLU -lX11 -lXxf86vm -lXrandr -lpthread -lXi -ldl -lglut 

INCLUDES	= 	-I../../ \
				-I $(HOME_PATH)/libs/$(LIB_GLFW_DIR)/include/ \
				-I $(HOME_PATH)/libs/$(LIB_GLEW_DIR)/include/ \
				-I $(HOME_PATH)/libs/$(LIB_FREEGLUT_DIR)/include/

OPENG_LIBS	=	$(HOME_PATH)/libs/$(LIB_GLFW_DIR)/src/libglfw3.a \
				$(HOME_PATH)/libs/$(LIB_GLEW_DIR)/lib/libGLEW.a \
				$(HOME_PATH)/libs/$(LIB_FREEGLUT_DIR)/lib/libglut.a

name = libopengl.so

SRCS = libopengl.cpp
OBJS = $(SRCS:.cpp=.o)
DEPENDS = $(SRCS:.cpp=.d)

%.o: %.cpp
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) : $(_LWHITE)$<$(_END)$(_DIM) ------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" "LibOpenGL"
	@$(CXX) $(CFLAGS) $(INCLUDES) -MD -c $< -o $@
	
all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(SHARED_LIB_FLAGS) -o $(NAME) $(OBJS) $(LIB_FLAGS) $(OPENG_LIBS)
	@printf "$(_LWHITE)- $(_LCYAN)%s$(_END) $(_LWHITE)Compiled !$(_END)$(_DIM) --------- $(_END)$(_LWHITE)[$(_LGREEN)✔$(_LWHITE)]$(_END)\n" $(NAME)

clean:
	@rm -rf $(OBJS) $(DEPENDS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPENDS)