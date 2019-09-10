/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:33:19 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:33:20 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_champ(t_val *h, int max, int flag)
{
	int len;
	int start;
	int end;

	len = 0;
	while (h)
	{
		start = flag == 0 ? h->is_nm_start : h->is_cmnt_start;
		end = flag == 0 ? h->is_nm_end : h->is_cmnt_end;
		if (h->istxt && start)
			len = h->len;
		if (h->istxt && end)
			break ;
		h = h->next;
	}
	len > max && !flag ?
	ft_putstr_fd("Error - Maximum name length exceeded\n", 2) : 0;
	len > max && flag ?
	ft_putstr_fd("Error - Maximum comment length exceeded\n", 2) : 0;
	return (len > max ? TRUE : FALSE);
}

int		check_header(t_val *a, t_val *b)
{
	t_val *t;

	t = b;
	while (a)
	{
		while (b)
		{
			if (a->istxt && b->istxt && a != b && ((a->is_nm_start
			&& b->is_nm_start) || (a->is_cmnt_start && b->is_cmnt_start)))
			{
				ft_putstr_fd("\033[0;31m", 2);
				ft_putstr_fd(a->error_l, 2);
				ft_putstr_fd("\033[0m", 2);
				ft_putstr_fd("\nError - Header\n", 2);
				return (TRUE);
			}
			b = b->next;
		}
		b = t;
		a = a->next;
	}
	return (FALSE);
}

int		check_end(t_val *h)
{
	while (h)
	{
		if (!h->istxt && (h->is_nm_middle || h->is_nm_end
		|| h->is_cmnt_middle || h->is_cmnt_end))
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(h->error_l, 2);
			ft_putstr_fd("\033[0m", 2);
			ft_putstr_fd("\nError - Header\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		check_nm_and_cmnt(t_val *h)
{
	int nm;
	int cmnt;

	nm = 0;
	cmnt = 0;
	while (h)
	{
		if (h->is_nm_start)
			nm = 1;
		if (h->is_cmnt_start)
			cmnt = 1;
		if (!h->istxt && nm + cmnt != 2)
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(h->error_l, 2);
			ft_putstr_fd("\033[0m", 2);
			ft_putstr_fd("\nError - Header\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

void	its_something(t_val *h)
{
	while (h)
	{
		if (!h->istxt && !h->iscmd && !h->islbl)
			h->istxt = 1;
		h = h->next;
	}
}
