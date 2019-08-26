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

void	printer_valid(t_val *head)
{
	ft_putendl("nm1\tnm2\tnm3\tcom1\tcom2\tcom3\tlen\tcmd\tmark\tline\n");
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
		ft_putnbr(head->iscmd);
		ft_putstr("\t");
		ft_putnbr(head->ismark);
		ft_putstr("\t");
		head->line ? ft_putendl(head->line) : 0;
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
		{
			if (s[begin] == chars[i])
			{
				begin++;
				flag = 1;
			}
		}
		if (flag == 0)
			break ;
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
		{
			if (s[end] == chars[i])
			{
				end--;
				flag = 1;
			}
		}
		if (flag == 0)
			break ;
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

void	find_begin_champ(t_val *h, char *find, int comment)
{
	while (h)
	{
		if (ft_strstr(h->line, find) && count_chars(h->line, '\"') > 0
		&& ft_strstr(h->line, find) - ft_strchr(h->line, '\"') < 0)
		{
			h->is_nm_start = comment == 0 ? 1 : 0;
			h->is_cmnt_start = comment == 1 ? 1 : 0;
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
			h->is_nm_end = comment == 0 ? 1 : 0;
			h->is_cmnt_end = comment == 1 ? 1 : 0;
		}
		else if (t == 1 && count_chars(h->line, '\"') < 2 && h->next)
		{
			h->next->is_nm_middle = comment == 0 ? 1 : 0;
			h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
		}
		h = h->next;
	}
}

void	find_end_champ(t_val *h, int comment)
{
	int t;

	t = 0;
	while (h)
	{
		t = comment == 0 ? h->is_nm_middle : h->is_cmnt_middle;
		if (t == 1 && count_chars(h->line, '\"') == 0 && h->next)
		{
			h->next->is_nm_middle = comment == 0 ? 1 : 0;
			h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
		}
		else if (t == 1 && count_chars(h->line, '\"') == 1)
		{
			h->is_nm_end = comment == 0 ? 1 : 0;
			h->is_cmnt_end = comment == 1 ? 1 : 0;
		}
		h = h->next;
	}
}

t_val	*read_content(t_val **h, int comment)
{
	int t;

	t = 0;
	while (h)
	{
		t = comment == 0 ? h->is_nm_middle : h->is_cmnt_middle;
		if (t == 1 && count_chars(h->line, '\"') == 0 && h->next)
		{
			h->next->is_nm_middle = comment == 0 ? 1 : 0;
			h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
		}
		else if (t == 1 && count_chars(h->line, '\"') == 1)
		{
			h->is_nm_end = comment == 0 ? 1 : 0;
			h->is_cmnt_end = comment == 1 ? 1 : 0;
		}
		h = h->next;
	}
}

void	vocabulary(t_val *h)
{
	find_begin_champ(h, NAME_CMD_STRING, 0);
	find_begin_champ(h, COMMENT_CMD_STRING, 1);
	find_middle_champ(h, 0);
	find_middle_champ(h, 1);
	find_end_champ(h, 0);
	find_end_champ(h, 1);
	h = read_content(&h, 0);
	h = read_content(&h, 1);
}

void	create_valid_roll(char *s)
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
	vocabulary(head);
	printer_valid(head);
}

int		main(int ac, char **av)
{
	char *s;

	s = NULL;
	// s = skip_chars_at_first(ft_strdup("  		  001  		  "), " 	");
	// printf("%s\n", s);
	// free(s);
	// s = skip_chars_from_end(ft_strdup("  		  001  		  "), " 	");
	// printf("%s\n", s);
	// free(s);
	if (ac == 2 && !ft_strcmp(av[1] + ft_strlen(av[1]) - 2, ".s"))
	{
		s = read_file(av[1]);
		s = del_comments(s);
		create_valid_roll(s);
		//printf("%s\n", s);
		free(s);
	}
	else
		ft_putendl("Неверное количество файлов или файл не с расширением .s");
	return (0);
}
