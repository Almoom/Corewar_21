/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:30:58 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:31:00 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		scroll_chars_to_end(char *s, char *chars, int ch)
{
	int		begin;
	int		i;
	int		flag;

	begin = 0;
	if (s[begin] == ch)
		return (FALSE);
	while (s[begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[begin] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
		begin++;
	}
	return (s[begin] == ch ? TRUE : FALSE);
}

int		scroll_chars(char *s, char *chars)
{
	int		begin;
	int		i;
	int		flag;

	begin = 0;
	while (s[begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
			if (s[begin] == chars[i])
				flag = 1;
		if (flag == 0)
			break ;
		begin++;
	}
	return (s[begin]);
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

int		just_0(t_val *h)
{
	t_val *t;

	t = h;
	return (0);
}

int		just_1(t_val *h)
{
	t_val *t;

	t = h;
	return (1);
}
