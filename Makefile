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

CC = gcc -Wall -Wextra -Werror
NAME = asm
SRC = asm.c
TEST = test_binary/hash_at_header

make:
	@rm -f /Users/ljalikak/Documents/corewar_21/test_binary/*.cor
	@$(CC) -g -o $(NAME) $(SRC) lib_add.c scroll.c skip.c valid_struct.c read_args.c read_args_add.c write_file.c check_header.c read_nm_cmnt.c check_file.c check_code.c split_and_build.c check_code_add.c num_and_quote.c /Users/ljalikak/Documents/corewar_21/libft/libft.a
	./$(NAME) $(TEST).s
	# chmod 777 $(TEST).cor
	hexdump $(TEST).cor > test.txt
	./asm2 $(TEST).s
	hexdump $(TEST).cor > test1.txt
	diff test.txt test1.txt

clean:
	@rm -f /Users/ljalikak/Documents/corewar_21/libft/*.o

fclean: clean
	rm -f $(NAME)

re: fclean make
