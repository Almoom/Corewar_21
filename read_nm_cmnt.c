/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_nm_cmnt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:39:30 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:39:31 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

void	find_end_champ_add(t_val *h, int comment)
{
	h->next->is_nm_middle = comment == 0 ? 1 : 0;
	h->next->is_cmnt_middle = comment == 1 ? 1 : 0;
	h->istxt = 1;
}

void	find_end_champ(t_val *h, int comment)
{
	int		t;
	char	*tmp;

	t = 0;
	tmp = NULL;
	while (h)
	{
		t = comment == 0 ? h->is_nm_middle : h->is_cmnt_middle;
		if (t == 1 && count_chars(h->line, '\"') == 0 && h->next
		&& !h->next->is_cmnt_start && !h->next->is_nm_start)
			find_end_champ_add(h, comment);
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
			(h)->data = quote1 ? ft_strdup(quote1) : NULL;
			(h)->len = ft_strlen(quote1);
			free(quote1);
			flag = 1;
		}
		if (((h)->is_cmnt_start == 1 || (h)->is_nm_start == 1)
		&& flag == 1 && !(h)->data)
		{
			(h)->data = quote2 ? ft_strdup(quote2) : NULL;
			(h)->len = ft_strlen(quote2);
			free(quote2);
			break ;
		}
		(h) = (h)->next;
	}
}
