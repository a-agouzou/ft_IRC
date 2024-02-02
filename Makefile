# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 09:54:25 by afatir            #+#    #+#              #
#    Updated: 2024/02/02 13:47:01 by khbouych         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98  -g  -fsanitize=address,undefined
SRCS = Server.cpp Client.cpp Channel.cpp main.cpp  Mode.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -g -o $(NAME) $(OBJS)

%.o: %.cpp Server.hpp Client.hpp Channel.hpp 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

khalid :
	make fclean
	make clean
	git add .
	git commit -m "auto commit khbouych"
	git push

.PHONY: all clean fclean re