# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pkhienko42 <pkhienko42@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/24 14:32:33 by sklaokli          #+#    #+#              #
#    Updated: 2025/12/13 17:47:01 by pkhienko42       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	webserv

OBJ_DIR		:=	bin
INC_DIR		:=	include
SRC_DIR		:=	src

ROOT_FILES	:=	main.cpp

# SRC_FILES	:=	Config.cpp \
# 				Poller.cpp \
# 				Request.cpp \
# 				Response.cpp \
# 				Server.cpp \
# 				Webserv.cpp

SRC_FILES	:=  Server.cpp \
				Webserv.cpp

ROOT_OBJ	:=	$(addprefix $(OBJ_DIR)/, $(ROOT_FILES:%.cpp=%.o))
SRC_OBJ		:=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:%.cpp=%.o))

OBJ			:=	$(ROOT_OBJ) $(SRC_OBJ)

CXX			:=	c++
WFLAGS		:=	-Wall -Wextra -Werror
CXXFLAGS	:=	-std=c++98 -pedantic
INCLUDE		:=	-I$(INC_DIR)

COMPILE		:=	$(CXX) $(WFLAGS) $(CXXFLAGS) $(INCLUDE)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(COMPILE) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(COMPILE) -c $< -o $@

$(NAME): $(OBJ)
	$(COMPILE) $(OBJ) -o $(NAME)

clean:
	@ rm -rf $(OBJ_DIR)

fclean: clean
	@ rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re