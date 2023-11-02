# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/11/02 07:14:58 by ttikanoj         ###   ########.fr        #
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

SRC_FILES = DynamicBuffer \
			User \
			Uvector \
			Cvector \
			Message \
			IRCServer \
			handleIO \
			Channel \
			ChannelBatchMode \
			connectToUser \
			handleUser \
			executeCommand \
			Operator \
			split \
			wildcard \
			cmd_pass \
			cmd_nick \
			cmd_user \
			cmd_motd \
			cmd_oper \
			cmd_quit \
			cmd_ping \
			cmd_pong \
			cmd_away \
			cmd_kill \
			cmd_mode \
			commandUtils \
			cmd_privmsg \
			cmd_notice \
			chan_cmd_invite \
			chan_cmd_join \
			chan_cmd_kick \
			chan_cmd_part \
			chan_cmd_topic \
			chan_cmd_mode \
			Logger

INC_FILES = DynamicBuffer \
			Logger \
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
