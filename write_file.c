/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 20:24:21 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 20:24:23 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_value_in_memory(char *memory, int pos, int value, int size)
{
	int		i;
	char	*byte;

	i = 0;
	byte = (char *)(&value);
	while (i < size)
	{
		*(memory + (pos + size - i - 1)) = byte[i];
		i++;
	}
}

void	write_int(int fd, int pos, int value, int size)
{
	char	s[1000];
	int		i;

	i = 0;
	ft_bzero(s, 1000);
	ft_value_in_memory(s, pos, value, size);
	while (i < size)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	write_text(int fd, t_val *h, int flag, int max)
{
	char	*s;
	int		i;
	int		start;

	i = 0;
	while (h)
	{
		start = flag == 0 ? h->is_nm_start : h->is_cmnt_start;
		if (start)
			s = h->data;
		h = h->next;
	}
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	while (i < max)
	{
		ft_putchar_fd(0, fd);
		i++;
	}
}

void	write_cmds(int fd, t_val *h)
{
	while (h)
	{
		if (h->n_cmd > 0)
		{
			write_int(fd, 0, h->n_cmd, 1);
			if (g_tab_reg[h->n_cmd - 1][0] == 1)
				write_int(fd, 0, h->type, 1);
			if (h->arg[0]->data)
				write_int(fd, 0, h->arg[0]->dec, h->arg[0]->len);
			if (h->arg[1]->data)
				write_int(fd, 0, h->arg[1]->dec, h->arg[1]->len);
			if (h->arg[2]->data)
				write_int(fd, 0, h->arg[2]->dec, h->arg[2]->len);
		}
		h = h->next;
	}
}

void	creat_file(t_val *h, char *name, int code_size)
{
	int fd;

	if ((fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0)
		return ;
	write_int(fd, 0, COREWAR_EXEC_MAGIC, 4);
	write_text(fd, h, 0, PROG_NAME_LENGTH);
	write_int(fd, 0, 0, 4);
	write_int(fd, 0, code_size, 4);
	write_text(fd, h, 1, COMMENT_LENGTH);
	write_int(fd, 0, 0, 4);
	write_cmds(fd, h);
	close(fd);
	ft_putstr("Writing output program to ");
	ft_putendl(name);
}
