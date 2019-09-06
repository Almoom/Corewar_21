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
#include <string.h>

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
	{1, 4}, //"ld",		//2
	{1, 4}, //"st",		//3
	{1, 4}, //"add",	//4
	{1, 4}, //"sub",	//5
	{1, 4}, //"and",	//6
	{1, 4}, //"or",		//7
	{1, 4}, //"xor",	//8
	{0, 2}, //"zjmp",	//9
	{1, 2}, //"ldi",	//10
	{1, 2}, //"sti",	//11
	{0, 2}, //"fork",	//12
	{1, 4}, //"lld",	//13
	{1, 2}, //"lldi",	//14
	{0, 2}, //"lfork",	//15
	{1, 4}, //"aff",	//16
};

void	printer_valid(t_val *head)
{
	//ft_putendl("nm1\tnm2\tnm3\tcom1\tcom2\tcom3\tlen\ttxt\tcmd\t№\ta1\ta2\ta3\tx0\tready\tlbl\tname\tdata\tline\n");
	ft_putendl("txt\tcmd\t№\tlen\ttype\t\tt_i\ta1\tda1\tlen1\ta2\tda2\tlen2\ta3\tda3\tlen3\tready_l\tlbl\tname\tdata\t\tline\n");
	while (head)
	{
		// ft_putnbr(head->is_nm_start);
		// ft_putstr("\t");
		// ft_putnbr(head->is_nm_middle);
		// ft_putstr("\t");
		// ft_putnbr(head->is_nm_end);
		// ft_putstr("\t");
		// ft_putnbr(head->is_cmnt_start);
		// ft_putstr("\t");
		// ft_putnbr(head->is_cmnt_middle);
		// ft_putstr("\t");
		// ft_putnbr(head->is_cmnt_end);
		//ft_putstr("\t");
		ft_putnbr(head->istxt);
		ft_putstr("\t");
		// if (head->istxt == 0)
		// {
			ft_putnbr(head->iscmd);
			ft_putstr("\t");
			ft_putnbr(head->n_cmd);
			ft_putstr("\t");
			ft_putnbr(head->len);
			ft_putstr("\t");
			head->arg[0]->type ? ft_putstr(head->arg[0]->type) : ft_putstr("  ");
			head->arg[1]->type ? ft_putstr(head->arg[1]->type) : ft_putstr("  ");
			head->arg[2]->type ? ft_putstr(head->arg[2]->type) : ft_putstr("  ");
			head->arg[3]->type ? ft_putstr(head->arg[3]->type) : ft_putstr("  ");
			ft_putstr("\t");
			ft_putnbr(head->type);
			ft_putstr("\t");
			ft_putnbr(head->arg[0]->dec);
			ft_putstr("\t");
			head->arg[0]->data ? ft_putstr(head->arg[0]->data) : 0;
			ft_putstr("\t");
			ft_putnbr(head->arg[0]->len);
			ft_putstr("\t");
			ft_putnbr(head->arg[1]->dec);
			ft_putstr("\t");
			head->arg[1]->data ? ft_putstr(head->arg[1]->data) : 0;
			ft_putstr("\t");
			ft_putnbr(head->arg[1]->len);
			ft_putstr("\t");
			ft_putnbr(head->arg[2]->dec);
			ft_putstr("\t");
			head->arg[2]->data ? ft_putstr(head->arg[2]->data) : 0;
			ft_putstr("\t");
			ft_putnbr(head->arg[2]->len);
			ft_putstr("\t");
			ft_putnbr(head->r);
			ft_putstr("\t");
			ft_putnbr(head->islbl);
			ft_putstr("\t");
			head->n_lbl ? ft_putstr(head->n_lbl) : 0;
			ft_putstr("\t");
			head->data ? ft_putstr(head->data) : 0;
			ft_putstr("\t\t");
			head->line ? ft_putendl(head->line) : ft_putchar('\n');
		//}
		head = head->next;
	}
}

char	*skip_chars_at_first(char *s, char *chars)
{
	int		begin;
	int		i;
	int		flag;
	char	*tmp;

	begin = -1;
	tmp = NULL;
	while (s[++begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[begin] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
	}
	if (*(s + begin) == '\0')
	{
		free(s);
		return (NULL);
	}
	tmp = ft_strdup(s + begin);
	free(s);
	return (tmp);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	s = ft_strnew(n);
	while (src[i] && i < n)
	{
		s[i] = src[i];
		i++;
	}
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
	tmp = ft_strndup(s, end + 1);
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
			while (s[i] && s[i] != '\n')
				i++;
		t[j] = s[i];
		j++;
		i++;
	}
	free(s);
	return (t);
}

t_val	*create_list_valid(char *s, char *all)
{
	t_val *list;
	int i;

	i = 0;
	if (!(list = (t_val*)ft_memalloc(sizeof(t_val))))
		return (NULL);
	list->line = ft_strdup(s);
	list->error_l = ft_strdup(s);
	//if (all)
	//	list->all = ft_strdup(all);
	while (i < 4)
	{
		if (!(list->arg[i] = (t_ar*)ft_memalloc(sizeof(t_ar))))
			return (NULL);
		i++;
	}
	return (list);
}

t_val	*creator_valid(t_val *head, char *s)
{
	t_val *tmp;
	t_val *list;

	tmp = head;
	list = NULL;
	while (head->next)
		head = head->next;
	list = create_list_valid(s, NULL);
	head->next = list;
	list->prev = head;
	return (tmp);
}

void	del_split(char ***str)
{
	int i;
	char **s;

	s = *str;
	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	*str = NULL;
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
			(h)->data = quote1 ? ft_strdup(quote1) : ft_strnew(0);
			(h)->len = ft_strlen(quote1);
			free(quote1);
			flag = 1;
		}
		if (((h)->is_cmnt_start == 1 || (h)->is_nm_start == 1)
		&& flag == 1 && !(h)->data)
		{
			(h)->data = quote2 ? ft_strdup(quote2) : ft_strnew(0);
			(h)->len = ft_strlen(quote2);
			free(quote2);
			break ;
		}
		(h) = (h)->next;
	}
}

void 	cut_space(t_val *h)
{
	while (h)
	{
		if (h->istxt == 0 && h->line)
		{
			h->line = skip_chars_at_first(h->line, " 	");
			h->line = skip_chars_from_end(h->line, " 	");
		}
		if (h->arg[0]->data)
		{
			h->arg[0]->data = skip_chars_at_first(h->arg[0]->data, " 	");
			h->arg[0]->data = skip_chars_from_end(h->arg[0]->data, " 	");
		}
		if (h->arg[1]->data)
		{
			h->arg[1]->data = skip_chars_at_first(h->arg[1]->data, " 	");
			h->arg[1]->data = skip_chars_from_end(h->arg[1]->data, " 	");
		}
		if (h->arg[2]->data)
		{
			h->arg[2]->data = skip_chars_at_first(h->arg[2]->data, " 	");
			h->arg[2]->data = skip_chars_from_end(h->arg[2]->data, " 	");
		}
		h = h->next;
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
	//printf("%s -- %d\n", s, begin);
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
		if (ft_strnstr(h->line, g_tab_com[i], ft_strlen(g_tab_com[i]))
		&& ((h->line + ft_strlen(g_tab_com[i]))[0] == ' '
		|| (h->line + ft_strlen(g_tab_com[i]))[0] == '\t'
		|| (h->line + ft_strlen(g_tab_com[i]))[0] == DIRECT_CHAR))
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
			h->len++;
			if (g_tab_reg[num][0] == 1)
			{
				h->arg[0]->type = ft_strdup("00");
				h->arg[1]->type = ft_strdup("00");
				h->arg[2]->type = ft_strdup("00");
				h->arg[3]->type = ft_strdup("00");
				h->len++;
			}
			if (h->line && (h->islbl == 1 || h->iscmd == 1))
				h->line = skip_chars_at_first(h->line, " 	");
		}
		h = h->next;
	}
}

void	find_label(t_val *h)
{
	char t[1];

	t[0] = LABEL_CHAR;
	while (h)
	{
		if ((h)->istxt == 0 && ft_strchr(h->line, LABEL_CHAR)
		&& scroll_chars(h->line, LABEL_CHARS, LABEL_CHAR))
		{
			h->islbl = 1;
			h->n_lbl = ft_strndup
			(h->line, ft_strchr(h->line, LABEL_CHAR) - h->line);
			h->line = skip_chars_at_first(h->line, LABEL_CHARS);
			if ((h->line[1] && h->line[1] != LABEL_CHAR) || h->line[1] == '\0')
				h->line = skip_chars_at_first(h->line, t);
			if (h->line)
				h->line = skip_chars_at_first(h->line, " 	");
			if (!h->line)
				h->r = 1;
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

char	*ft_strnrev_free(char *s, int count, int flag)
{
	char	*t;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	k = count - i;
	t = ft_strnew(count + 1);
	ft_memset(t, '0', count);
	while (k < count)
	{
		t[k] = s[i - 1];
		k++;
		i--;
	}
	flag == 1 ? free(s) : 0;
	return (t);
}

char	*ft_itoa_16(int n, int count)
{
	char *s;
	char arr[2] = {0, 0};
	unsigned int num;

	num = (unsigned int)n;
	s = ft_strnew(0);
	while(num > 0)
	{
		arr[0] = num % 16 + (num % 16 > 9 ? 'a' - 10 : '0');
		s = ft_strjoin_free(s, arr, 1, 0);
		num /= 16;
	}
	return (s = ft_strnrev_free(s, count, 1));
}

int		build_dec_from_bytes(char *s)
{
	int rez;
	int len;
	int i;

	rez = 0;
	i = ft_strlen(s) - 1;
	len = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == '1')
			rez += ft_power(2, len - i);
		i--;
	}
	free(s);
	return (rez);
}

int		build_byte_types(t_val *h)
{
	char *rez;
	int i;

	rez = NULL;
	i = 0;
	while (i < 4)
	{
		rez = ft_strjoin_free(rez, h->arg[i]->type, 1, 0);
		i++;
	}
	//printf("%s\n", rez);
	return (build_dec_from_bytes(rez));
}

void	build_0x(t_val *h)
{
	//ft_putendl(h->error_l);
	//free(h->data);
	while (h)
	{
		if (!h->istxt)
		{
			h->data = ft_strdup("0x");
			h->data = ft_strjoin_free(h->data, ft_itoa_16(h->n_cmd, 2), 1, 1);
			if (h->n_cmd > 0 && g_tab_reg[h->n_cmd - 1][0] != 0)
			{
				h->type = build_byte_types(h);
				h->data = ft_strjoin_free
				(h->data, ft_itoa_16(h->type, 2), 1, 1);
			}
			h->data = ft_strjoin_free(h->data, ft_itoa_16
			(h->arg[0]->dec, h->arg[0]->len * 2), 1, 1);
			h->data = ft_strjoin_free(h->data, ft_itoa_16
			(h->arg[1]->dec, h->arg[1]->len * 2), 1, 1);
			h->data = ft_strjoin_free(h->data, ft_itoa_16
			(h->arg[2]->dec, h->arg[2]->len * 2), 1, 1);
		}
		h = h->next;
	}
}

int		not_valid_arg(t_val *t)
{
	t->islbl = 0;
	t->iscmd = 0;
	ft_putstr("Lexical error at ");
	if (t->error_l)
		ft_putendl(t->error_l);
	return (1);
}

int		valid_args(t_val *t)
{
	t->r = 1;
	return (0);
}

int		find_down_lbl(t_val *h, t_val *t, int num, int shift)
{
	int count;

	count = 0;
	while (h)
	{
		if (h->islbl && !ft_strcmp(h->n_lbl, t->arg[num]->data + shift))
			return (count);
		count += h->len + h->arg[0]->len + h->arg[1]->len + h->arg[2]->len;
		if (h->r == 0)
			return (FALSE);
		h = h->next;
	}
	return (FALSE);
}

int		find_up_lbl(t_val *h, t_val *t, int num)
{
	int count;

	count = 0;
	while (h)
	{
		if (h == t)
			return (-1 * count);
		count += h->len + h->arg[0]->len + h->arg[1]->len + h->arg[2]->len;
		if (h->r == 0)
			return (FALSE);
		h = h->next;
	}
	return (FALSE);
}

int		find_byte_to_lbl(t_val *h, t_val *t, int num, int shift)
{
	while (h)
	{
		if (h == t)
			return (find_down_lbl(h, t, num, shift));
		if (h->islbl && !ft_strcmp(h->n_lbl, t->arg[num]->data + shift))
			return (find_up_lbl(h, t, num));
		if (h)
			h = h->next;
	}
	t->iscmd = 0;
	return (FALSE);
}

int		dir(t_val *h, t_val *t, int num)
{
	if (t->arg[num]->data[0] == DIRECT_CHAR && (scroll_chars(t->arg[num]->data + 1, "0123456789", '\0') || (t->arg[num]->data[1] == '-' && scroll_chars(t->arg[num]->data + 2, "0123456789", '\0'))))
	{
		t->arg[num]->len = g_tab_reg[t->n_cmd - 1][1];
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data + 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
		{
			free(t->arg[num]->type);
			t->arg[num]->type = ft_strdup("10");
		}
	}
	else if (t->arg[num]->data[0] == DIRECT_CHAR && t->arg[num]->data[1]
	== LABEL_CHAR && check_lbl(h, t->arg[num]->data + 2))
	{
		t->arg[num]->len = g_tab_reg[t->n_cmd - 1][1];
		t->arg[num]->dec = t->r ? find_byte_to_lbl(h, t, num, 2) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
		{
			free(t->arg[num]->type);
			t->arg[num]->type = ft_strdup("10");
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int		reg(t_val *t, int num)
{
	if (t->arg[num]->data[0] == 'r'
	&& scroll_chars(t->arg[num]->data + 1, "0123456789", '\0')
	&& (ft_strlen(t->arg[num]->data) == 3
	|| ft_strlen(t->arg[num]->data) == 2)
	&& ft_strcmp(t->arg[num]->data, "r0")
	&& ft_strcmp(t->arg[num]->data, "r00"))
	{
		t->arg[num]->len = 1;
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data + 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
		{
			free(t->arg[num]->type);
			t->arg[num]->type = ft_strdup("01");
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int		ind(t_val *h, t_val *t, int num)
{
	if ((scroll_chars(t->arg[num]->data, "0123456789", '\0') || (t->arg[num]->data[0] == '-' && scroll_chars(t->arg[num]->data + 1, "0123456789", '\0'))))
	{
		t->arg[num]->len = 2;
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
		{
			free(t->arg[num]->type);
			t->arg[num]->type = ft_strdup("11");
		}
	}
	else if (t->arg[num]->data[0] == LABEL_CHAR
	&& check_lbl(h, t->arg[num]->data + 1))
	{
		t->arg[num]->len = 2;
		t->arg[num]->dec = t->r ? find_byte_to_lbl(h, t, num, 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
		{
			free(t->arg[num]->type);
			t->arg[num]->type = ft_strdup("11");
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

int		read_args(t_val *h, t_val *t, int (*err)(t_val*), int (*rght)(t_val*))
{
	if (t->n_cmd == 1 || t->n_cmd == 9 || t->n_cmd == 12 || t->n_cmd == 15)
		return (!dir(h, t, 0) ? err(t) : rght(t));
	if (t->n_cmd == 16)
		return (!reg(t, 0) ? err(t) : rght(t));
	if (t->n_cmd == 4 || t->n_cmd == 5)
		return ((!reg(t, 0) || !reg(t, 1) || !reg(t, 2)) ? err(t) : rght(t));
	if (t->n_cmd == 2 || t->n_cmd == 13)
		return ((!dir(h, t, 0) && !ind(h, t, 0)) || !reg(t, 1)
		? err(t) : rght(t));
	if (t->n_cmd == 10 || t->n_cmd == 14)
		return ((!dir(h, t, 0) && !ind(h, t, 0) && !reg(t, 0)) || (!reg(t, 1)
		&& !dir(h, t, 1)) || !reg(t, 2) ? err(t) : rght(t));
	if (t->n_cmd == 6 || t->n_cmd == 7 || t->n_cmd == 8)
		return ((((!dir(h, t, 0) && !ind(h, t, 0) && !reg(t, 0)))
		|| (!dir(h, t, 1) && !ind(h, t, 1) && !reg(t, 1))
		|| !reg(t, 2)) ? err(t) : rght(t));
	if (t->n_cmd == 3)
		return ((!reg(t, 0) || (!ind(h, t, 1) && !reg(t, 1)))
		? err(t) : rght(t));
	if (t->n_cmd == 11)
		return (!reg(t, 0) || (!reg(t, 2) && !dir(h, t, 2))
		|| (!dir(h, t, 1) && !ind(h, t, 1) && !reg(t, 1))
		? err(t): rght(t));
	return (0);
}

int		read_cmd(t_val *h, int (*err)(t_val*), int (*rght)(t_val*))
{
	t_val *t;

	t = h;
	while (t)
	{
		if (t->n_cmd > 0)
			read_args(h, t, err, rght);
		t = t->next;
	}
	//printer_valid(h);
	return (FALSE);
}

int		split_len(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	split_by_comma(t_val *h)
{
	char **arr;

	while (h)
	{
		if (h->n_cmd > 0)
		{
			arr = ft_strsplit(h->line, SEPARATOR_CHAR);
			if (h->line && ((count_chars(h->line, SEPARATOR_CHAR) < 3
			&& split_len(arr) == count_chars(h->line, SEPARATOR_CHAR) + 1)
			|| (count_chars(h->line, SEPARATOR_CHAR) == 0)))
			{
				h->arg[0]->data = ft_strdup(arr[0]);
				h->arg[1]->data = arr[1] ? ft_strdup(arr[1]) : NULL;
				h->arg[2]->data = arr[1] && arr[2] ? ft_strdup(arr[2]) : NULL;
			}
			else
			{
				h->iscmd = 0;
				h->islbl = 0;
			}
			del_split(&arr);
		}
		h = h->next;
	}
}

void	check_dubl_label(t_val *a, t_val *b)
{
	t_val *t;

	t = b;
	while (a)
	{
		while (b)
		{
			if (a->islbl && b->islbl && a!= b && !ft_strcmp(a->n_lbl, b->n_lbl))
				a->islbl = 0;
			b = b->next;
		}
		b = t;
		a = a->next;
	}
}

int		check_champ(t_val *h, int max, int flag)
{
	int count;
	int len;
	int start;
	int end;

	count = 0;
	len = 0;
	while (h)
	{
		start = flag == 0 ? h->is_nm_start : h->is_cmnt_start;
		end = flag == 0 ? h->is_nm_end : h->is_cmnt_end;
		if (h->istxt && start)
		{
			count++;
			len = h->len;
		}
		if (h->istxt && end)
		{
			count++;
			break ;
		}
		h = h->next;
	}
	return ((count == 2 && len <= max) ? TRUE : FALSE);
}

void	print_error_cmd(char *s, char *find)
{
	char *t;
	int len;

	t = ft_strstr(s, find);
	len = t - s;
	// printf("%s\n", find);
	// printf("%d\n", len);
}

int		check_all(t_val *h)
{
	char *t;

	t = h->all;
	while (h)
	{
		if (!h->istxt && !h->islbl && !h->iscmd)
		{
			//print_error_cmd(t, h->error_l);
			//ft_putendl(h->error_l);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		rght_null(t_val *h)
{
	return (1);
}

void	ft_value_in_memory(char *memory, int pos, int value, int size)
{
	int i;
	char *byte;

	i = 0;
	byte = (char *)(&value);
	while (i < size)
	{
		*(memory + (pos + size - i - 1)) = byte[i];
		i++;
	}
}

void	write_int(int fd, int pos, int value, int size)
{
	char s[1000];
	int i;

	i = 0;
	ft_bzero(s, 1000);
	ft_value_in_memory(s, pos, value, size);
	while (i < size)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	write_text(int fd, t_val *h, int flag, int max)
{
	char *s;
	int i;
	int start;

	i = 0;
	while (h)
	{
		start = flag == 0 ? h->is_nm_start : h->is_cmnt_start;
		if (start)
			s = h->data;
		h = h->next;
	}
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	while (i < max)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
}

void	write_cmds(int fd, t_val *h)
{
	while (h)
	{
		if (h->n_cmd > 0)
		{
			write_int(fd, 0, h->n_cmd, 1);
			if (g_tab_reg[h->n_cmd - 1][0] == 1)
				write_int(fd, 0, h->type, 1);
			if (h->arg[0]->data)
				write_int(fd, 0, h->arg[0]->dec, h->arg[0]->len);
			if (h->arg[1]->data)
				write_int(fd, 0, h->arg[1]->dec, h->arg[1]->len);
			if (h->arg[2]->data)
				write_int(fd, 0, h->arg[2]->dec, h->arg[2]->len);
		}
		h = h->next;
	}
}

void	creat_file(t_val *h, char *name, int code_size)
{
	int fd;

	if ((fd = open(name, O_RDWR | O_CREAT | O_APPEND | O_TRUNC)) < 0)
		return ;
	write_int(fd, 0, COREWAR_EXEC_MAGIC, 4);
	write_text(fd, h, 0, PROG_NAME_LENGTH);
	write_int(fd, 0, 0, 4);
	write_int(fd, 0, code_size, 4);
	write_text(fd, h, 1, COMMENT_LENGTH);
	write_int(fd, 0, 0, 4);
	write_cmds(fd, h);
	close(fd);
	ft_putstr("Writing output program to ");
	ft_putendl(name);
}

int		code_size(t_val *h)
{
	int rez;

	rez = 0;
	while (h)
	{
		if (h->n_cmd > 0 && h->arg[0] && h->arg[1] && h->arg[2])
			rez += h->len + h->arg[0]->len + h->arg[1]->len + h->arg[2]->len;
		h = h->next;
	}
	return (rez);
}

void	del_list_valid(t_val **del)
{
	ft_memdel((void**)(&(*del)->line));
	ft_memdel((void**)(&(*del)->error_l));
	ft_memdel((void**)(&(*del)->data));
	ft_memdel((void**)(&(*del)->n_lbl));
	ft_memdel((void**)(&(*del)->all));
	ft_memdel((void**)(&(*del)->arg[0]->type));
	ft_memdel((void**)(&(*del)->arg[1]->type));
	ft_memdel((void**)(&(*del)->arg[2]->type));
	ft_memdel((void**)(&(*del)->arg[3]->type));
	ft_memdel((void**)(&(*del)->arg[0]->data));
	ft_memdel((void**)(&(*del)->arg[1]->data));
	ft_memdel((void**)(&(*del)->arg[2]->data));
	free((*del)->arg[0]);
	free((*del)->arg[1]);
	free((*del)->arg[2]);
	free((*del)->arg[3]);
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

char	*find_quote(char *s, int ch, int n1, int n2)
{
	char *t;
	int i;
	int count;
	int j;

	t = ft_strnew(ft_strlen(s) + 1);
	i = -1;
	count = 0;
	j = -1;
	while (s[++i])
	{
		if (count == n1)
		{
			while (s[i] != ch)
			{
				t[++j] = s[i];
				i++;
			}
		}
		if (count == n2)
			break ;
		if (s[i] == ch)
			count++;
	}
	//printf("%s\n", t);
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

int		rght_one(t_val *h)
{
	return (0);
}

void	parse_commands(t_val *h, char *name)
{
	char *newname;
	int size;

	size = 0;
	newname = ft_strjoin_free
	(ft_strndup(name, ft_strlen(name) - 2), ft_strdup(".cor"), 1, 1);
	split_by_comma(h);
	if (!check_all(h))
	{
		cut_space(h);
		read_cmd(h, &not_valid_arg, &valid_args);
		read_cmd(h, &rght_null, &rght_one);
		build_0x(h);
		if (!check_all(h))
		{

		 	// if (((size = code_size(h))) <= CHAMP_MAX_SIZE)
				creat_file(h, newname, code_size(h));
			// else
			// 	ft_putendl("Champion code too long (Max length 682)");
		}
	}
	free(newname);
	//printer_valid(h);//////
}

void	vocabulary(t_val *h, char *quote1, char *quote2, char *name)
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
	check_dubl_label(h, h);
	write_command_num(h);
	// if (!check_champ(h, PROG_NAME_LENGTH, 0))
	// 	ft_putendl("Champion name too long (Max length 128)");
	// else if (!check_champ(h, COMMENT_LENGTH, 1))
	// 	ft_putendl("Champion comment too long (Max length 2048)");
	//else
	//printer_valid(h);
	if (!check_all(h))
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
				head = create_list_valid(t[i], s);
			else
				head = creator_valid(head, t[i]);
		}
		i++;
	}
	del_split(&t);
	vocabulary(head, quote1, quote2, name);
	del_roll_valid(&head);
}

void	print_error_endfile(char *s)
{
	int count;
	int i;

	count = ft_strlen(s) - 1;
	i = 1;
	ft_putstr("Syntax error at token [TOKEN][");
	if (count_chars(s, '\n') + 1 < 100)
		ft_putchar('0');
	if (count_chars(s, '\n') + 1 < 10)
		ft_putchar('0');
	ft_putnbr(count_chars(s, '\n') + 1);
	ft_putchar(':');
	while (s[count] != '\n')
	{
		i++;
		count--;
	}
	if (i < 100)
		ft_putchar('0');
	if (i < 10)
		ft_putchar('0');
	ft_putnbr(i);
	ft_putendl("] END \"(null)\"");
}

void 	print_error_args(int ac)
{
	ft_putstr("Wrong number of arguments (given ");
	ft_putnbr(ac - 1);
	ft_putendl(", expected 1)");
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
			//ft_putendl("--");
			quote2 = find_quote(s, '\"', 3, 4);

			create_valid_roll(s, quote1, quote2, av[1]);
		}
		else
			print_error_endfile(s);
		free(s);
	}
	else if (ac != 2)
		print_error_args(ac);
	else
		ft_putendl
		("Syntax error at token [TOKEN][001:001] INDIRECT \"0000890\"");
	return (0);
}
