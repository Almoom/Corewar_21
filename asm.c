/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:17:16 by ljalikak          #+#    #+#             */
/*   Updated: 2019/08/25 17:17:17 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char *g_tab_com[16] =
{
	"live",
	"ld",
	"st",
	"add",
	"sub",
	"and",
	"or",
	"xor",
	"zjmp",
	"ldi",
	"sti",
	"fork",
	"lld",
	"lldi",
	"lfork",
	"aff",
};

int g_tab_reg[16][2] =
{
	{0, 4},
	{1, 4},
	{1, 4},
	{1, 4},
	{1, 4},
	{1, 4},
	{1, 4},
	{1, 4},
	{0, 2},
	{1, 2},
	{1, 2},
	{0, 2},
	{1, 4},
	{1, 2},
	{0, 2},
	{1, 4},
};

void	parse_commands(t_val *h, char *name)
{
	char	*newname;
	int		size;

	size = 0;
	if (check_dubl_label(h, h) || check_true_lbl(h) || check_true_cmd(h)
	|| check_true_args(h))
	{
		its_something(h);
		return ;
	}
	split_by_comma(h);
	if (check_all(h))
		return ;
	cut_space(h);
	read_cmd(h, &not_valid_arg, &valid_args);
	read_cmd(h, &just_1, &just_0);
	build_0x(h);
	newname = ft_strjoin_free(ft_strndup(name, ft_strlen(name) - 2),
	ft_strdup(".cor"), 1, 1);
	if (!check_all(h))
		creat_file(h, newname, code_size(h));
	free(newname);
}

void	vocabulary(t_val *h, char *quote1, char *quote2, char *name)
{
	find_begin_champ(h, NAME_CMD_STRING, 0);
	find_begin_champ(h, COMMENT_CMD_STRING, 1);
	find_middle_champ(h, 0);
	find_middle_champ(h, 1);
	find_end_champ(h, 0);
	find_end_champ(h, 1);
	if (check_end(h) || check_header(h, h) || check_nm_and_cmnt(h))
	{
		its_something(h);
		free(quote1);
		free(quote2);
		return ;
	}
	write_content(h, quote1, quote2);
	cut_space(h);
	find_label(h);
	write_command_num(h);
	if (check_champ(h, PROG_NAME_LENGTH, 0)
	|| check_champ(h, COMMENT_LENGTH, 1))
		return ;
	parse_commands(h, name);
}

void	create_valid_roll(char *s, char *quote1, char *quote2, char *name)
{
	char	**t;
	int		i;
	t_val	*head;
	int		count;

	t = ft_strsplit(s, '\n');
	i = 0;
	head = NULL;
	count = 0;
	while (t[i])
	{
		count += count_chars(t[i], '\"');
		if (scroll_spaces(t[i], count))
		{
			if (!head)
				head = create_list_valid(t[i]);
			else
				head = creator_valid(head, t[i]);
		}
		i++;
	}
	del_split(&t);
	vocabulary(head, quote1, quote2, name);
	del_roll_valid(&head);
}

char	*read_file(char *name)
{
	int		fd;
	char	*arr;

	arr = NULL;
	if ((fd = open(name, O_RDONLY)) < 0)
		return (NULL);
	ft_get_next_file(fd, &arr);
	close(fd);
	return (arr);
}

int		main(int ac, char **av)
{
	char *s;
	char *quote1;
	char *quote2;

	s = NULL;
	if (ac == 2 && !ft_strcmp(av[1] + ft_strlen(av[1]) - 2, ".s"))
	{
		if (!(s = read_file(av[1])))
		{
			print_not_found(av[1]);
			return (0);
		}
		s = del_comments(s);
		if (check_last_nl(s) && check_exist(s))
		{
			quote1 = find_quote(s, '\"', 1, 2);
			quote2 = find_quote(s, '\"', 3, 4);
			create_valid_roll(s, quote1, quote2, av[1]);
		}
		free(s);
	}
	else
		ft_putstr_fd("usage: ./asm sourcefile.s\n", 2);
	return (0);
}
