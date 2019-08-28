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
#include "op.h"

char *g_tab_com[16] =
{
	"live",	//1
	"ld",	//2
	"st",	//3
	"add",	//4
	"sub",	//5
	"and",	//6
	"or",	//7
	"xor",	//8
	"zjmp",	//9
	"ldi",	//10
	"sti",	//11
	"fork",	//12
	"lld",	//13
	"lldi",	//14
	"lfork",//15
	"aff",	//16
};

int g_tab_reg[16][2] =
{
	{0, 4}, //"live",	//1
	{1, 4}, //"ld",	//2
	{1, 4}, //"st",	//3
	{1, 4}, //"add",	//4
	{1, 4}, //"sub",	//5
	{1, 4}, //"and",	//6
	{1, 4}, //"or",	//7
	{1, 4}, //"xor",	//8
	{0, 2}, //"zjmp",	//9
	{1, 2}, //"ldi",	//10
	{1, 2}, //"sti",	//11
	{0, 2}, //"fork",	//12
	{1, 4}, //"lld",	//13
	{1, 2}, //"lldi",	//14
	{0, 2}, //"lfork",//15
	{1, 4}, //"aff",	//16
};

void	printer_valid(t_val *head)
{
	ft_putendl("nm1\tnm2\tnm3\tcom1\tcom2\tcom3\tlen\ttxt\tcmd\t№\ta1\ta2\ta3\tready\tlbl\tname\t№\tdata\tline\n");
	while (head)
	{
		ft_putnbr(head->is_nm_start);
		ft_putstr("\t");
		ft_putnbr(head->is_nm_middle);
		ft_putstr("\t");
		ft_putnbr(head->is_nm_end);
		ft_putstr("\t");
		ft_putnbr(head->is_cmnt_start);
		ft_putstr("\t");
		ft_putnbr(head->is_cmnt_middle);
		ft_putstr("\t");
		ft_putnbr(head->is_cmnt_end);
		ft_putstr("\t");
		ft_putnbr(head->len);
		ft_putstr("\t");
		ft_putnbr(head->istxt);
		ft_putstr("\t");
		ft_putnbr(head->iscmd);
		ft_putstr("\t");
		ft_putnbr(head->n_cmd);
		ft_putstr("\t");
		ft_putnbr(head->a1);
		ft_putstr("\t");
		ft_putnbr(head->a2);
		ft_putstr("\t");
		ft_putnbr(head->a3);
		ft_putstr("\t");
		ft_putnbr(head->ready);
		ft_putstr("\t");
		ft_putnbr(head->islbl);
		ft_putstr("\t");
		head->n_lbl ? ft_putstr(head->n_lbl) : 0;
		ft_putstr("\t");
		ft_putnbr(head->numlbl);
		ft_putstr("\t");
		head->data ? ft_putstr(head->data) : 0;
		ft_putstr("\t");
		head->line ? ft_putendl(head->line) : ft_putchar('\n');
		head = head->next;
	}
}

char	*skip_chars_at_first(char *s, char *chars)
{
	int		begin;
	int		i;
	int		flag;
	char	*tmp;

	begin = 0;
	tmp = NULL;
	while (s[begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[begin] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
		begin++;
	}
	if (*(s + begin) == '\0')
		return (NULL);
	tmp = ft_strdup(s + begin);
	free(s);
	return (tmp);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!(s = (char*)malloc(sizeof(*src) * (ft_strlen(src) + 1)))
		|| ft_strlen(src) == 9223372036854775807)
		return (NULL);
	while (src[i] && i <= n)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*skip_chars_from_end(char *s, char *chars)
{
	int		end;
	int		i;
	int		flag;
	char	*tmp;

	end = ft_strlen(s) - 1;
	tmp = NULL;
	while (s[end])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[end] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
		end--;
	}
	tmp = ft_strndup(s, end);
	free(s);
	return (tmp);
}

int		ft_get_next_file(const int fd, char **line)
{
	int			len;
	char		buf[BUFF_SIZE + 1];
	static char	*arr[10240];
	char		*tmp;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line || fd > 10240)
		return (-1);
	len = ((arr[fd] == 0) ? 0 : 1);
	if (!(arr[fd]))
		arr[fd] = ft_strnew(0);
	while ((len = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[len] = '\0';
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
	}
	*line = arr[fd];
	arr[fd] = NULL;
	if ((*line)[0] == '\0')
		return (0);
	return (1);
}

char	*read_file(char *name)
{
	int		fd;
	char	*arr;

	fd = open(name, O_RDONLY);
	arr = NULL;
	if (fd >= 0)
		ft_get_next_file(fd, &arr);
	close(fd);
	return (arr);
}

char	*del_comments(char *s)
{
	char *t;
	int i;
	int j;
	int count;

	t = ft_strnew(ft_strlen(s));
	i = 0;
	j = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			count++;
		if (count % 2 == 0
		&& (s[i] == COMMENT_CHAR || s[i] == ALT_COMMENT_CHAR))
			while (s[i] != '\n')
				i++;
		t[j] = s[i];
		j++;
		i++;
	}
	free(s);
	return (t);
}

t_val	*create_list_valid(char *s)
{
	t_val *list;

	if (!(list = (t_val*)ft_memalloc(sizeof(*list))))
		return (NULL);
	list->line = ft_strdup(s);
	list->n_cmd = 0;
	return (list);
}

t_val	*creator_valid(t_val *head, char *s)
{
	t_val *tmp;

	tmp = head;
	while (head->next)
	{
		head = head->next;
	}
	head->next = create_list_valid(s);
	return (tmp);
}

void	del_split(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

int		count_chars(char *s, int ch)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ch)
			count++;
		i++;
	}
	return (count);
}

int		scroll_spaces(char *s, int count)
{
	int i;

	i = 0;
	while (s[i])
	{
		if ((count % 2 == 0 && s[i] != ' ' && s[i] != '\t') || (count % 2 != 0))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int 	check_left(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\"')
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void	find_begin_champ(t_val *h, char *find, int comment)
{
	while (h)
	{
		if (ft_strstr(h->line, find)
		&& check_left(ft_strstr(h->line, find) + ft_strlen(find))
		&& count_chars(h->line, '\"') > 0 && count_chars(h->line, '\"') < 3
		&& ft_strstr(h->line, find) - ft_strchr(h->line, '\"') < 0)
		{
			h->is_nm_start = comment == 0 ? 1 : 0;
			h->is_cmnt_start = comment == 1 ? 1 : 0;
			h->istxt = 1;
		}
		h = h->next;
	}
}

void	find_middle_champ(t_val *h, int comment)
{
	int t;

	t = 0;
	while (h)
	{
		t = comment == 0 ? h->is_nm_start : h->is_cmnt_start;
		if (t == 1 && count_chars(h->line, '\"') == 2)
		{
			h->line = skip_chars_from_end(h->line, " 	");
			if (h->line[ft_strlen(h->line) - 1] == '\"')
			{
				h->is_nm_end = comment == 0 ? 1 : 0;
				h->is_cmnt_end = comment == 1 ? 1 : 0;
				h->istxt = 1;
			}
		}
		else if (t == 1 && count_chars(h->line, '\"') < 2 && h->next)
		{
			h->next->is_nm_middle = comment == 0 ? 1 : 0;
			h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
			h->istxt = 1;
		}
		h = h->next;
	}
}

void	find_end_champ(t_val *h, int comment)
{
	int t;
	char *tmp;

	t = 0;
	tmp = NULL;
	while (h)
	{
		t = comment == 0 ? h->is_nm_middle : h->is_cmnt_middle;
		if (t == 1 && count_chars(h->line, '\"') == 0 && h->next)
		{
			h->next->is_nm_middle = comment == 0 ? 1 : 0;
			h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
			h->istxt = 1;
		}
		else if (t == 1 && count_chars(h->line, '\"') == 1)
		{
			h->line = skip_chars_from_end(h->line, " 	");
			if (h->line[ft_strlen(h->line) - 1] == '\"')
			{
				h->is_nm_end = comment == 0 ? 1 : 0;
				h->is_cmnt_end = comment == 1 ? 1 : 0;
				h->istxt = 1;
			}
		}
		h = h->next;
	}
}

void	write_content(t_val *h, char *quote1, char *quote2)
{
	int flag;

	flag = 0;
	while ((h))
	{
		if (((h)->is_cmnt_start == 1 || (h)->is_nm_start == 1) && flag == 0)
		{
			(h)->data = ft_strdup(quote1);
			(h)->len = ft_strlen(quote1);
			free(quote1);
			flag = 1;
		}
		if (((h)->is_cmnt_start == 1 || (h)->is_nm_start == 1)
		&& flag == 1 && !(h)->data)
		{
			(h)->data = ft_strdup(quote2);
			(h)->len = ft_strlen(quote2);
			free(quote2);
			break ;
		}
		(h) = (h)->next;
	}
}

void 	cut_space(t_val *h)
{
	while ((h))
	{
		if ((h)->istxt == 0)
		{
			(h)->line = skip_chars_at_first((h)->line, " 	");
			(h)->line = skip_chars_from_end((h)->line, " 	");
		}
		(h) = (h)->next;
	}
}

int		scroll_chars(char *s, char *chars, int ch)
{
	int		begin;
	int		i;
	int		flag;

	begin = 0;
	if (s[begin] == ch)
		return (FALSE);
	while (s[begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[begin] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
		begin++;
	}
	return (s[begin] == ch ? TRUE : FALSE);
}

int		check_cmd(t_val *h)
{
	int i;
	char *t;

	i = 0;
	t = NULL;
	if (!(h->line))
		return (-1);
	while (i < 16)
	{
		if (ft_strnstr(h->line, g_tab_com[i], ft_strlen(g_tab_com[i])))
		{
			t = ft_strdup(h->line + ft_strlen(g_tab_com[i]));
			free(h->line);
			h->line = t;
			return (i);
		}
		i++;
	}
	return (-1);
}

void	write_command_num(t_val *h)
{
	int num;

	num = -1;
	while (h)
	{
		if (h->istxt != 1 && (num = check_cmd(h)) >= 0)
		{
			if (h->islbl != 1 && (h->line[0] == ' ' || h->line[0] == '\t'
			|| h->line[0] == '%'))
				h->iscmd = 1;
			h->n_cmd = num + 1;
			if (h->line && (h->islbl == 1 || h->iscmd == 1))
				h->line = skip_chars_at_first(h->line, " 	");
		}
		h = h->next;
	}
}

void	find_label_data(t_val *h)
{
	t_val *t;

	t = NULL;
	while (h)
	{
		// if (h->islbl == 1 && ft_strchr(h->line, LABEL_CHAR) + 1)
		// 	h->data = skip_chars_at_first
		// 	(ft_strdup(ft_strchr(h->line, LABEL_CHAR) + 1), " 	");
		if (h->islbl == 1 && !(h->line))
		{
			t = h;
			while (t)
			{
				if (t->islbl != 1)
					break ;
				t = t->next;
			}
			if (t)
				h->line = ft_strjoin_free(h->line, t->line, 1, 0);
		}
		h = h->next;
	}
}

void	find_label(t_val *h)
{
	int count;
	char t[1];

	count = 1;
	t[0] = LABEL_CHAR;
	while (h)
	{
		if ((h)->istxt == 0 && ft_strchr(h->line, LABEL_CHAR)
		&& scroll_chars(h->line, LABEL_CHARS, LABEL_CHAR))
		{
			h->islbl = 1;
			h->numlbl = count;
			h->n_lbl = ft_strndup
			(h->line, ft_strchr(h->line, LABEL_CHAR) - h->line - 1);
			h->line = skip_chars_at_first(h->line, LABEL_CHARS);
			if ((h->line[1] && h->line[1] != LABEL_CHAR) || h->line[1] == '\0')
				h->line = skip_chars_at_first(h->line, t);
			if (h->line)
				h->line = skip_chars_at_first(h->line, " 	");
			count++;
		}
		h = h->next;
	}
}

int		check_int(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (i == 0 && s[i] == '-')
			i++;
		if (!s[i] || !ft_isdigit(s[i]))
			return (FALSE);
	}
	return (TRUE);
}

// loop:
//         sti r1, %:live, %1 1+1+1+2+2
// live:
//         live %0           1+4
//         ld %0, r2         1+1+4+1
//         zjmp %:loop //-19 1+2

// void	parse_live(t_val *h, t_val *t)
// {
// 	int flag;
//
// 	flag = 0;
// 	// if (h->line[0] == DIRECT_CHAR && ft_strnstr(h->line + 1, "0x", 2) && scroll_chars(h->line + 3, "0123456789", '\0'))
// 	// 	printf("--%s\n", "16");
// 	if (t->line[0] == DIRECT_CHAR && check_int(t->line + 1)
// 	&& !ft_strchr(t->line, '+'))
// 	{
// 		t->a1 = ft_atoi(t->line + 1);
// 		t->ready = 1;
// 	}
// 	if (t->line[0] == DIRECT_CHAR && t->line[1] == LABEL_CHAR
// 	&& scroll_chars(h->line + 2, LABEL_CHARS, '\0'))
// 	{
// 		while (h)
// 		{
// 			if (ft_strcmp(h->n_lbl, t->line) && h->ready == 1)
// 				;
// 			h = h->next;
// 		}
// 	}
// }
//
// void	parse_lbl_args(t_val *h)
// {
// 	t_val *t;
//
// 	t = h;
// 	while (t)
// 	{
// 		if (t->n_cmd >= 0 && t->islbl == 1)
// 		{
// 			t->n_cmd == 1 ? parse_live(h, t) : 0;
// 		}
// 		t = t->next;
// 	}
// }

int		check_lbl(t_val *h, char *s)
{
	while (h)
	{
		if (h->n_lbl && !ft_strcmp(h->n_lbl, s))
			return (TRUE);
		h = h->next;
	}
	return (FALSE);
}

int		len_loner_dir(t_val *h, int cmd, char *s)
{
	if (s[0] == DIRECT_CHAR && ((check_int(s + 1) && !ft_strchr(s, '+'))
	|| (s[1] == LABEL_CHAR && check_lbl(h, s + 2))))
		return (g_tab_reg[cmd - 1][0] + g_tab_reg[cmd - 1][1] + 1);
	return (0);
}

int		len_loner_reg(t_val *h, int cmd, char *s)
{
	if (s[0] == 'r' && scroll_chars(s + 1, "0123456789", '\0')
	&& ft_atoi(s + 1) <= REG_NUMBER )
		return (g_tab_reg[cmd - 1][0] + g_tab_reg[cmd - 1][1] + 1);
	return (0);
}

int		len_cmd_args(t_val *h, int cmd, char *s)
{
	int len;

	len = 0;
	if (cmd == 1 || cmd == 9 || cmd == 12 || cmd == 15)
		return (len_loner_dir(h, cmd, s));
	if (cmd == 16)
		return (len_loner_reg(h, cmd, s));
	if (cmd == 2)
		return (len_ld(h, cmd, s));
	return (0);
}

void	write_command_len(t_val *h)
{
	t_val *t;

	t = h;
	while (t)
	{
		if (t->n_cmd >= 0)
			t->len = len_cmd_args(h, t->n_cmd, t->line);
		t = t->next;
	}
}

void	vocabulary(t_val *h, char *quote1, char *quote2)
{
	find_begin_champ(h, NAME_CMD_STRING, 0);
	find_begin_champ(h, COMMENT_CMD_STRING, 1);
	find_middle_champ(h, 0);
	find_middle_champ(h, 1);
	find_end_champ(h, 0);
	find_end_champ(h, 1);
	write_content(h, quote1, quote2);
	cut_space(h);
	find_label(h);
	find_label_data(h);
	write_command_num(h);
	write_command_len(h);

	//parse_lbl_args(h);
	printer_valid(h);


	//в конце проверить длины
}

void	del_list_valid(t_val **del)
{
	ft_memdel((void**)(&(*del)->line));
	ft_memdel((void**)(&(*del)->data));
	ft_memdel((void**)(&(*del)->n_lbl));
	free(*del);
}

void	del_roll_valid(t_val **head)
{
	t_val *tmp;

	if (!(*head))
		return ;
	while ((*head))
	{
		tmp = (*head)->next;
		del_list_valid(head);
		*head = tmp;
	}
}

void	create_valid_roll(char *s, char *quote1, char *quote2)
{
	char	**t;
	int		i;
	t_val	*head;
	int count;

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
	del_split(t);
	vocabulary(head, quote1, quote2);
	//printer_valid(head);
	del_roll_valid(&head);
}

char	*find_quote(char *s, int ch, int n1, int n2)
{
	char *t;
	int i;
	int count;
	int j;

	t = ft_strnew(ft_strlen(s));
	i = 0;
	count = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ch)
			count++;
		if (count == n2)
			break ;
		if (count == n1 && j == 0)
			i++;
		if (count == n1)
		{
			t[j] = s[i];
			j++;
		}
		i++;
	}
	return (t);
}

int		check_last_nl(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	while (s[len])
	{
		if (s[len] == '\n')
			return (TRUE);
		if (s[len] != ' ' && s[len] != '\t')
			break ;
		len--;
	}
	return (FALSE);
}

int		main(int ac, char **av)
{
	char *s;
	char *quote1;
	char *quote2;

	s = NULL;
	if (ac == 2 && !ft_strcmp(av[1] + ft_strlen(av[1]) - 2, ".s"))
	{
		s = read_file(av[1]);
		s = del_comments(s);
		if (check_last_nl(s))
		{
			quote1 = find_quote(s, '\"', 1, 2);
			quote2 = find_quote(s, '\"', 3, 4);
			create_valid_roll(s, quote1, quote2);
		}
		else
			ft_putendl("после последней команды нет \\n");
		free(s);
	}
	else
		ft_putendl("Неверное количество файлов или файл не с расширением .s");
	return (0);
}
