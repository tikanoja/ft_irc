# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/10/11 13:14:36 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

S = src
I = inc
O = obj

CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 \
	-Wconversion -Wshadow -I $I #-g -fsanitize=address -static-libsan

SRC_FILES = main \
			CircularBuffer \
			User \
			Uvector \
			Cvector \
			Message \
			IRCServer \
			connectToUser \
			handleUser \
			executeCommand \
			cmd_pass \
			cmd_nick \
			cmd_user \
			cmd_quit \
			chan_cmd_join \
			Channel \
			cmd_ping \
			cmd_pong
#			cmd_away
#			cmd_kill
#			cmd_lusers
#			cmd_notice
#			cmd_privmsg
#			cmd_who
#			cmd_whois
#			cmd_mode
#			cmd_oper
#			cmd_squit
#			chan_invite
#			chan_list
#			chan_mode
#			chan_mode
#			chan_names
#			chan_part
#			chan_topic
#			Channel
# 			Registration

INC_FILES = CircularBuffer \
			User \
			Uvector \
			Cvector \
			Message \
			Error \
			Reply \
			Commands \
			IRCServer \
			Channel \

SRC = $(foreach FILE,$(SRC_FILES),$(shell find $S -type f -name "$(FILE).cpp"))
OBJ = $(patsubst $S/%,$O/%,$(SRC:.cpp=.o))

OBJ_DIRS = $(dir $(OBJ))

HEADER = $(addprefix $I/,$(addsuffix .hpp,$(INC_FILES)))

all: $(NAME)

$O:
	@mkdir -p $@ $(OBJ_DIRS)

print:
	@echo $(HEADER)

$O/%.o: $S/%.cpp $(HEADER) | $O
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
