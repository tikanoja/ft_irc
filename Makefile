# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/10/26 09:51:05 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

S = src
I = inc
O = obj
T = test_dir

CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 \
	-Wconversion -Wshadow -I $I -g -fsanitize=address -static-libsan

SRC_FILES = CircularBuffer \
			User \
			Uvector \
			Cvector \
			Message \
			IRCServer \
			Channel \
			connectToUser \
			handleUser \
			executeCommand \
			Operator \
			split \
			cmd_pass \
			cmd_nick \
			cmd_user \
			cmd_oper \
			cmd_quit \
			chan_cmd_join \
			cmd_ping \
			cmd_pong \
			cmd_privmsg \
			cmd_away \
			cmd_kill \
			cmd_mode \
			commandUtils \
			chan_cmd_part \
			chan_cmd_topic
#			cmd_notice
#			chan_cmd_mode
#			chan_invite
#			chan_mode


INC_FILES = CircularBuffer \
			User \
			Uvector \
			Cvector \
			Operator \
			Message \
			Error \
			Reply \
			Commands \
			Utils \
			IRCServer \
			Channel

SRC = $(foreach FILE,$(SRC_FILES),$(shell find $S -type f -name "$(FILE).cpp"))
OBJ = $(patsubst $S/%,$O/%,$(SRC:.cpp=.o))


OBJ_DIRS = $(dir $(OBJ))

HEADER = $(addprefix $I/,$(addsuffix .hpp,$(INC_FILES)))

all: $(NAME)

$O:
	@mkdir -p $@ $(OBJ_DIRS)

print: $(TST)
	@echo $^

$O/%.o: $S/%.cpp $(HEADER) | $O
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ) src/main.cpp
	@$(CC) $(FLAGS) -c src/main.cpp -o obj/main.o
	@$(CC) $(FLAGS) $^ -o $@

clean:
	@rm -rf $O $T

fclean: clean
	@rm -f $(NAME)

re: fclean all

test: $(OBJ) test.cpp | $T
	@$(CC) $(FLAGS) -c test.cpp -o $T/test.o
	@$(CC) $(FLAGS) $(OBJ) $T/test.o -o $T/test

$T:
	@mkdir -p $@


.PHONY: all clean fclean re
