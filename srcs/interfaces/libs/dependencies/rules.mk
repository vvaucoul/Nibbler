# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    rules.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvaucoul <vvaucoul@student.42.Fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/22 14:14:53 by vvaucoul          #+#    #+#              #
#    Updated: 2022/12/03 19:38:51 by vvaucoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX					= 	clang++-12
INCLUDES			= 	-I. 
SHARED_LIB_FLAGS	= 	-shared

STD_VERSION			= 	17
CFLAGS				=	-g3 -fPIC -std=c++$(STD_VERSION) $(INCLUDES) -Wall -Wextra -Werror 

HOME_PATH			=	$(HOME)