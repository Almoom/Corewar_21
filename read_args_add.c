/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args_add.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:58:46 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:58:48 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		not_valid_arg(t_val *t)
{
	t->islbl = 0;
	t->iscmd = 0;
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

int		find_up_lbl(t_val *h, t_val *t)
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
			return (find_up_lbl(h, t));
		if (h)
			h = h->next;
	}
	t->iscmd = 0;
	return (FALSE);
}
