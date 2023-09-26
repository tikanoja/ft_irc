# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/09/26 10:40:26 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj

CC = c++

SRC_FILES = main.cpp IRCServer.cpp User.cpp Channel.cpp

SRC = $(addprefix $(SRC_DIR)/,$(SRC_FILES))

OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 \
	-Wconversion -Wshadow -g -fsanitize=address -static-libsan

all: $(OBJ_DIR) $(NAME)


$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(FLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

SERVER = server
CLIENT = client

print: src/OneShotClient.cpp
	@echo $(CC) $(FLAGS) $< -o $@
	
test: $(SERVER) $(CLIENT)

$(SERVER): src/OneShotServer.cpp #to be removed !!!!!!!
	$(CC) $(FLAGS) $< -o $@

$(CLIENT): src/OneShotClient.cpp #to be removed !!!!!!!
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(SERVER) $(CLIENT)

re: fclean all

.PHONY: all clean fclean re
