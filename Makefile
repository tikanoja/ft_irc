# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: djagusch <djagusch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 22:43:37 by tuukka            #+#    #+#              #
#    Updated: 2023/09/29 11:47:10 by djagusch         ###   ########.fr        #
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
	User
# Message \
# Channel \
# Registration
	
INC_FILES = IRCServer \
	CircularBuffer \
	User
#	Message
# 	Channel \
# 	Error \
# 	Reply

SRC = $(addprefix $S/,$(addsuffix .cpp,$(SRC_FILES)))

OBJ = $(patsubst $S/%,$O/%,$(SRC:.cpp=.o))

HEADER = $(addprefix $I/,$(addsuffix .hpp,$(INC_FILES)))



all: $(NAME)

$O:
	mkdir -p $O

print:
	@echo $(HEADER)

$O/%.o: $S/%.cpp $(HEADER) | $O
	echo $(OBJ) $@
	$(CC) $(FLAGS) -I$I -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf $O

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
