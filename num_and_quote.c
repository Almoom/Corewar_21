/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_and_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 21:04:10 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 21:04:11 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_command_num(t_val *h)
{
	int num;

	num = -1;
	while (h)
	{
		if (h->istxt != 1 && (num = check_cmd(h)) >= 0)
		{
			if (h->islbl != 1 && (h->line[0] == ' ' || h->line[0] == '\t'
			|| h->line[0] == '%' || h->line[0] == '-'))
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

char	*find_quote(char *s, int ch, int n1, int n2)
{
	char	*t;
	int		i;
	int		count;
	int		j;

	t = ft_strnew(ft_strlen(s) + 1);
	i = -1;
	count = 0;
	j = -1;
	while (s[++i])
	{
		if (count == n1)
		{
			while (s[i] && s[i] != ch)
			{
				t[++j] = s[i];
				i++;
			}
		}
		if (count == n2 || !s[i])
			break ;
		if (s[i] == ch)
			count++;
	}
	return (t);
}
