/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_code_add.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:59:05 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:59:06 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_num_args(t_val *t, char **arr)
{
	int n;
	int flag;

	n = split_len(arr);
	flag = 0;
	if ((t->n_cmd == 1 || t->n_cmd == 9 || t->n_cmd == 12 || t->n_cmd == 15
	|| t->n_cmd == 16) && n != 1)
		flag = 1;
	if ((t->n_cmd == 2 || t->n_cmd == 3 || t->n_cmd == 13) && n != 2)
		flag = 1;
	if ((t->n_cmd == 4 || t->n_cmd == 5 || t->n_cmd == 6 || t->n_cmd == 7
	|| t->n_cmd == 8 || t->n_cmd == 10 || t->n_cmd == 11 || t->n_cmd == 14)
	&& n != 3)
		flag = 1;
	if (flag == 1)
	{
		t->iscmd = 0;
		t->islbl = 0;
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

int		check_cmd(t_val *h)
{
	int		i;
	char	*t;

	i = 0;
	t = NULL;
	if (!(h->line))
		return (-1);
	while (i < 16)
	{
		if (ft_strnstr(h->line, g_tab_com[i], ft_strlen(g_tab_com[i]))
		&& ((h->line + ft_strlen(g_tab_com[i]))[0] == ' '
		|| (h->line + ft_strlen(g_tab_com[i]))[0] == '\t'
		|| (h->line + ft_strlen(g_tab_com[i]))[0] == DIRECT_CHAR
		|| (h->line + ft_strlen(g_tab_com[i]))[0] == '-'))
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

void	find_label(t_val *h)
{
	char t[1];

	t[0] = LABEL_CHAR;
	while (h)
	{
		if (h->istxt == 0 && ft_strchr(h->line, LABEL_CHAR)
		&& scroll_chars_to_end(h->line, LABEL_CHARS, LABEL_CHAR))
		{
			h->islbl = 1;
			h->n_lbl = ft_strndup(h->line,
			ft_strchr(h->line, LABEL_CHAR) - h->line);
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
