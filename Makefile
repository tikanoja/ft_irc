# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/10/04 19:28:08 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

S = src
I = inc
O = obj

CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++11 \
	-Wconversion -Wshadow -I$I #-g -fsanitize=address -static-libsan

SRC_FILES = main \
			IRCServer \
			ConnectToUser \
			CircularBuffer \
			User \
			Uverctor \
			Message \
			cmd_away \
			cmd_kill \
			cmd_lusers \
			cmd_notice \
			cmd_ping \
			cmd_pong \
			cmd_privmsg \
			cmd_who \
			cmd_whois \
			cmd_mode \
			cmd_nick \
			cmd_oper \
			cmd_pass \
			cmd_quit \
			cmd_squit \
			cmd_user
#			chan_invite
#			chan_join
#			chan_list
#			chan_mode
#			chan_mode
#			chan_names
#			chan_part
#			chan_topic
#			Channel
# 			Registration

INC_FILES = IRCServer \
			CircularBuffer \
			User \
			Uvector \
			Message \
			Commands \
			Error \
			Reply
#			Channel

SRC = $(foreach FILE,$(SRC_FILES),$(shell find $S -type f -name "$(FILE).cpp"))
OBJ = $(patsubst $S/%,$O/%,$(SRC:.cpp=.o))

OBJ_DIRS = $(dir $(OBJ))

HEADER = $(addprefix $I/,$(addsuffix .hpp,$(INC_FILES)))

all: $(NAME)

$O:
	mkdir -p $@ $(OBJ_DIRS)

print:
	@echo $(SRC)
	@echo $(OBJ_DIRS)

$O/%.o: $S/%.cpp $(HEADER) | $O
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
