/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:38:28 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:38:30 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*skip_chars_at_first_add(char *s, int n)
{
	char	*t;
	int		i;

	t = ft_strnew(ft_strlen(s));
	i = 0;
	while (s[n + i])
	{
		t[i] = s[n + i];
		i++;
	}
	return (t);
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
	if (s[begin] == '\0')
	{
		ft_memdel((void**)(&s));
		return (NULL);
	}
	tmp = skip_chars_at_first_add(s, begin);
	ft_memdel((void**)(&s));
	return (tmp);
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

void	cut_space(t_val *h)
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

char	*del_comments(char *s)
{
	char	*t;
	int		i;
	int		j;
	int		count;

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
