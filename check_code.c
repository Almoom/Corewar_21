/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:49:36 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:49:37 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_true_lbl(t_val *h)
{
	while (h)
	{
		if (h->line && !h->istxt && !h->iscmd && ft_strchr(h->line, LABEL_CHAR)
		&& scroll_chars(h->line, LABEL_CHARS) != LABEL_CHAR && !h->n_cmd)
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(h->error_l, 2);
			ft_putstr_fd("\033[0m", 2);
			ft_putstr_fd("\nError - Label is invalid\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		check_true_cmd(t_val *h)
{
	while (h)
	{
		if (h->line && !h->istxt && !h->iscmd && !h->n_cmd
		&& !ft_strchr(h->line, LABEL_CHAR))
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(h->error_l, 2);
			ft_putstr_fd("\033[0m", 2);
			ft_putstr_fd("\nError - Operation does not exist\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		check_true_args(t_val *h)
{
	while (h)
	{
		if (h->line && !h->istxt && !h->iscmd && h->n_cmd > 0 && (!h->islbl
		|| count_chars(h->line, SEPARATOR_CHAR) > 2))
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(h->error_l, 2);
			ft_putstr_fd("\033[0m", 2);
			ft_putstr_fd("\nError - Parameter is invalid\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		check_dubl_label(t_val *a, t_val *b)
{
	t_val *t;

	t = b;
	while (a)
	{
		while (b)
		{
			if (a->islbl && b->islbl && a != b
			&& !ft_strcmp(a->n_lbl, b->n_lbl))
			{
				ft_putstr_fd("\033[0;31m", 2);
				ft_putstr_fd(a->error_l, 2);
				ft_putstr_fd("\033[0m", 2);
				ft_putstr_fd("\nError - Label is duplicate\n", 2);
				return (TRUE);
			}
			b = b->next;
		}
		b = t;
		a = a->next;
	}
	return (FALSE);
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
