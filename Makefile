# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/09/17 23:52:03 by tuukka           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

SRC_FILES = main.cpp IRCServer.cpp User.cpp Channel.cpp

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	c++ $(FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	c++ $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
