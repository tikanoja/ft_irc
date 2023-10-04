# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/10/04 09:59:18 by djagusch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

S = src
I = inc
O = obj

CC = c++

FLAGS = -Wall -Wextra -Werror -pedantic -std=c++98 \
	-Wconversion -Wshadow #-g -fsanitize=address -static-libsan

SRC_FILES = main \
			IRCServer \
			CircularBuffer \
			User \
			Uverctor \
			Message \
			cmd_invite \
			cmd_join \
			cmd_list \
			cmd_mode \
			cmd_names \
			cmd_part \
			cmd_topic \
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
# 			Channel
# 			Registration
	
INC_FILES = IRCServer \
			CircularBuffer \
			User \
			Uvector \
			Commands
# 			Error 
# 			Reply
#			Message
# 			Channel

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
	$(CC) $(FLAGS) -I$I -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $< -o $@

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
