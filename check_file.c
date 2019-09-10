/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:44:47 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:44:48 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_exist(char *s)
{
	if (scroll_chars(s, " 	\n") == '\0')
	{
		ft_putstr_fd("Error - File is empty\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

int		check_last_nl(char *s)
{
	int len;

	len = ft_strlen(s) - 1;
	while (s[len])
	{
		if (s[len] == '\n')
			return (TRUE);
		if (s[len] != ' ' && s[len] != '\t')
			break ;
		len--;
	}
	ft_putstr_fd("Error - Not found '\\n' in the end\n", 2);
	return (FALSE);
}

void	print_not_found(char *s)
{
	ft_putstr_fd("Can't read source file ", 2);
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\n', 2);
}

int		check_all(t_val *h)
{
	char *s;

	s = NULL;
	while (h)
	{
		if (!h->istxt && !h->islbl && !h->iscmd)
		{
			if (h->error_l)
			{
				s = skip_chars_at_first(h->error_l, " 	");
				ft_putstr_fd("\033[0;31m", 2);
				ft_putstr_fd(s, 2);
				ft_putstr_fd("\033[0m", 2);
				free(s);
			}
			ft_putstr_fd("\nError - Parameter is invalid\n", 2);
			return (TRUE);
		}
		h = h->next;
	}
	return (FALSE);
}

int		check_left(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\"')
	{
		if (s[i] != ' ' && s[i] != '\t')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
