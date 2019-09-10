/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_and_build.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:54:09 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:54:11 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		split_by_comma_add(t_val *h, char **arr)
{
	return (h->line && ((count_chars(h->line, SEPARATOR_CHAR) < 3
	&& split_len(arr) == count_chars(h->line, SEPARATOR_CHAR) + 1)
	|| (count_chars(h->line, SEPARATOR_CHAR) == 0)));
}

void	split_by_comma(t_val *h)
{
	char **arr;

	while (h)
	{
		if (h->n_cmd > 0)
		{
			arr = ft_strsplit(h->line, SEPARATOR_CHAR);
			if (split_by_comma_add(h, arr))
			{
				h->arg[0]->data = ft_strdup(arr[0]);
				h->arg[1]->data = arr[1] ? ft_strdup(arr[1]) : NULL;
				h->arg[2]->data = arr[1] && arr[2] ? ft_strdup(arr[2]) : NULL;
				check_num_args(h, arr);
			}
			else
			{
				h->iscmd = 0;
				h->islbl = 0;
				del_split(&arr);
				break ;
			}
			del_split(&arr);
		}
		h = h->next;
	}
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
	char	*rez;
	int		i;

	rez = NULL;
	i = 0;
	while (i < 4)
	{
		rez = ft_strjoin_free(rez, h->arg[i]->type, 1, 0);
		i++;
	}
	return (build_dec_from_bytes(rez));
}

void	build_0x(t_val *h)
{
	while (h)
	{
		if (!h->istxt)
			if (h->n_cmd > 0 && g_tab_reg[h->n_cmd - 1][0] != 0)
				h->type = build_byte_types(h);
		h = h->next;
	}
}
