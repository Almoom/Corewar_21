/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:18:23 by ljalikak          #+#    #+#             */
/*   Updated: 2019/08/25 17:18:25 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "op.h"
# include "libft/libft.h"
# include "asm_struct.h"
# define TRUE 1
# define FALSE 0

int g_tab_reg[16][2];
char *g_tab_com[16];

/*
**	asm.c
*/

int		main(int ac, char **av);
char	*read_file(char *name);
void	create_valid_roll(char *s, char *quote1, char *quote2, char *name);
void	vocabulary(t_val *h, char *quote1, char *quote2, char *name);
void	parse_commands(t_val *h, char *name);

/*
**	lib_add.c
*/

int		split_len(char **s);
void	del_split(char ***str);
int		count_chars(char *s, int ch);
char	*ft_strndup(const char *src, size_t n);
int		ft_get_next_file(const int fd, char **line);

/*
**	scroll.c
*/

int		just_0(t_val *h);
int		just_1(t_val *h);
int		scroll_chars(char *s, char *chars);
int		scroll_spaces(char *s, int count);
int		scroll_chars_to_end(char *s, char *chars, int ch);

/*
**	skip.c
*/

char	*del_comments(char *s);
void	cut_space(t_val *h);
char	*skip_chars_at_first(char *s, char *chars);
char	*skip_chars_at_first_add(char *s, int n);
char	*skip_chars_from_end(char *s, char *chars);

/*
**	valid_struct.c
*/

t_val	*create_list_valid(char *s);
t_val	*creator_valid(t_val *head, char *s);
void	del_list_valid(t_val **del);
void	del_roll_valid(t_val **head);

/*
**	read_args.c
*/

int		read_cmd(t_val *h, int (*err)(t_val*), int (*rght)(t_val*));
int		read_args(t_val *h, t_val *t, int (*err)(t_val*), int (*rght)(t_val*));
int		dir(t_val *h, t_val *t, int num);
int		reg(t_val *t, int num);
int		ind(t_val *h, t_val *t, int num);

/*
**	read_args_add.c
*/

int		not_valid_arg(t_val *t);
int		valid_args(t_val *t);
int		find_byte_to_lbl(t_val *h, t_val *t, int num, int shift);
int		find_up_lbl(t_val *h, t_val *t);
int		find_down_lbl(t_val *h, t_val *t, int num, int shift);

/*
**	write_file.c
*/

void	creat_file(t_val *h, char *name, int code_size);
void	write_int(int fd, int pos, int value, int size);
void	ft_value_in_memory(char *memory, int pos, int value, int size);
void	write_text(int fd, t_val *h, int flag, int max);
void	write_cmds(int fd, t_val *h);

/*
**	check_header.c
*/

int		check_champ(t_val *h, int max, int flag);
int		check_header(t_val *a, t_val *b);
int		check_end(t_val *h);
int		check_nm_and_cmnt(t_val *h);
void	its_something(t_val *h);

/*
**	read_nm_cmnt.c
*/

void	write_content(t_val *h, char *quote1, char *quote2);
void	find_begin_champ(t_val *h, char *find, int comment);
void	find_middle_champ(t_val *h, int comment);
void	find_end_champ(t_val *h, int comment);
void	find_end_champ_add(t_val *h, int comment);

/*
**	check_file.c
*/

int		check_exist(char *s);
int		check_last_nl(char *s);
void	print_not_found(char *s);
int		check_all(t_val *h);
int		check_left(char *s);

/*
**	check_code.c
*/

int		check_true_lbl(t_val *h);
int		check_true_cmd(t_val *h);
int		check_true_args(t_val *h);
int		check_dubl_label(t_val *a, t_val *b);
int		code_size(t_val *h);

/*
**	check_code_add.c
*/

void	check_num_args(t_val *t, char **arr);
int		check_int(char *s);
int		check_lbl(t_val *h, char *s);
int		check_cmd(t_val *h);
void	find_label(t_val *h);

/*
**	split_and_build.c
*/

void	split_by_comma(t_val *h);
int		split_by_comma_add(t_val *h, char **arr);
void	build_0x(t_val *h);
int		build_byte_types(t_val *h);
int		build_dec_from_bytes(char *s);

/*
**	num_and_quote.c
*/

void	write_command_num(t_val *h);
char	*find_quote(char *s, int ch, int n1, int n2);

#endif
