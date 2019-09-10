/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:52:47 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:52:50 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		dir(t_val *h, t_val *t, int num)
{
	if (!t->arg[num]->data)
		return (FALSE);
	if (t->arg[num]->data[0] == DIRECT_CHAR
	&& (scroll_chars_to_end(t->arg[num]->data + 1, "0123456789", '\0')
	|| (t->arg[num]->data[1] == '-'
	&& scroll_chars_to_end(t->arg[num]->data + 2, "0123456789", '\0'))))
	{
		t->arg[num]->len = g_tab_reg[t->n_cmd - 1][1];
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data + 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
			t->arg[num]->type[0] = '1';
	}
	else if (t->arg[num]->data[0] == DIRECT_CHAR && t->arg[num]->data[1]
	== LABEL_CHAR && check_lbl(h, t->arg[num]->data + 2))
	{
		t->arg[num]->len = g_tab_reg[t->n_cmd - 1][1];
		t->arg[num]->dec = t->r ? find_byte_to_lbl(h, t, num, 2) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
			t->arg[num]->type[0] = '1';
	}
	else
		return (FALSE);
	return (TRUE);
}

int		reg(t_val *t, int num)
{
	if (!t->arg[num]->data)
		return (FALSE);
	if (t->arg[num]->data[0] == 'r'
	&& scroll_chars_to_end(t->arg[num]->data + 1, "0123456789", '\0')
	&& (ft_strlen(t->arg[num]->data) == 3
	|| ft_strlen(t->arg[num]->data) == 2)
	&& ft_strcmp(t->arg[num]->data, "r0")
	&& ft_strcmp(t->arg[num]->data, "r00"))
	{
		t->arg[num]->len = 1;
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data + 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
			t->arg[num]->type[1] = '1';
	}
	else
		return (FALSE);
	return (TRUE);
}

int		ind(t_val *h, t_val *t, int num)
{
	if (!t->arg[num]->data)
		return (FALSE);
	if ((scroll_chars_to_end(t->arg[num]->data, "0123456789", '\0')
	|| (t->arg[num]->data[0] == '-'
	&& scroll_chars_to_end(t->arg[num]->data + 1, "0123456789", '\0'))))
	{
		t->arg[num]->len = 2;
		t->arg[num]->dec = t->r ? ft_atoi(t->arg[num]->data) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
			ft_memset(t->arg[num]->type, '1', 2);
	}
	else if (t->arg[num]->data[0] == LABEL_CHAR
	&& check_lbl(h, t->arg[num]->data + 1))
	{
		t->arg[num]->len = 2;
		t->arg[num]->dec = t->r ? find_byte_to_lbl(h, t, num, 1) : 0;
		if (g_tab_reg[t->n_cmd - 1][0])
			ft_memset(t->arg[num]->type, '1', 2);
	}
	else
		return (FALSE);
	return (TRUE);
}

int		read_args(t_val *h, t_val *t, int (*err)(t_val*), int (*rght)(t_val*))
{
	if (t->n_cmd == 1 || t->n_cmd == 9 || t->n_cmd == 12 || t->n_cmd == 15)
		return (!dir(h, t, 0) ? err(t) : rght(t));
	else if (t->n_cmd == 16)
		return (!reg(t, 0) ? err(t) : rght(t));
	else if (t->n_cmd == 4 || t->n_cmd == 5)
		return ((!reg(t, 0) || !reg(t, 1) || !reg(t, 2)) ? err(t) : rght(t));
	else if (t->n_cmd == 2 || t->n_cmd == 13)
		return ((!dir(h, t, 0) && !ind(h, t, 0))
		|| !reg(t, 1) ? err(t) : rght(t));
	else if (t->n_cmd == 10 || t->n_cmd == 14)
		return ((!dir(h, t, 0) && !ind(h, t, 0) && !reg(t, 0)) || (!reg(t, 1)
		&& !dir(h, t, 1)) || !reg(t, 2) ? err(t) : rght(t));
	else if (t->n_cmd == 6 || t->n_cmd == 7 || t->n_cmd == 8)
		return ((((!dir(h, t, 0) && !ind(h, t, 0) && !reg(t, 0)))
		|| (!dir(h, t, 1) && !ind(h, t, 1) && !reg(t, 1))
		|| !reg(t, 2)) ? err(t) : rght(t));
	else if (t->n_cmd == 3)
		return ((!reg(t, 0) || (!ind(h, t, 1) && !reg(t, 1)))
		? err(t) : rght(t));
	else if (t->n_cmd == 11)
		return (!reg(t, 0) || (!reg(t, 2) && !dir(h, t, 2)) || (!dir(h, t, 1)
		&& !ind(h, t, 1) && !reg(t, 1)) ? err(t) : rght(t));
	else
		return (1);
	return (1);
}

int		read_cmd(t_val *h, int (*err)(t_val*), int (*rght)(t_val*))
{
	t_val	*t;
	int		flag;

	t = h;
	flag = 0;
	while (t)
	{
		if (t->n_cmd > 0)
			flag = read_args(h, t, err, rght);
		if (flag == 1)
			break ;
		t = t->next;
	}
	return (FALSE);
}
