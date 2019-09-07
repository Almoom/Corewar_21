# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/04 13:04:11 by ljalikak          #+#    #+#              #
#    Updated: 2019/04/04 13:04:14 by ljalikak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = asm
SRC = asm.c
TEST = test_error/label_error_1

make:
	@rm -f /Users/ljalikak/Documents/corewar_21/*.cor
	@$(CC) -g -o $(NAME) $(SRC) /Users/ljalikak/Documents/corewar_21/libft/libft.a
	./$(NAME) $(TEST).s
	# chmod 777 $(TEST).cor
	# hexdump $(TEST).cor > test.txt
	# ./asm2 $(TEST).s
	# hexdump $(TEST).cor > test1.txt
	# diff test.txt test1.txt

clean:
	@rm -f /Users/ljalikak/Documents/corewar_21/libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean make
