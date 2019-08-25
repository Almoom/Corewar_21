/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:23:59 by ljalikak          #+#    #+#             */
/*   Updated: 2019/04/19 18:26:35 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_getbuf(char **arr, char **line)
{
	char *tmp;
	char *str;

	if ((*arr)[0] == '\0')
		return (0);
	if ((str = ft_strchr(*arr, '\n')))
	{
		*str = '\0';
		*line = ft_strdup(*arr);
		tmp = ft_strdup(str + 1);
		free(*arr);
		if (tmp)
		{
			*arr = ft_strdup(tmp);
			free(tmp);
		}
	}
	else
	{
		*line = ft_strdup(*arr);
		ft_memdel((void **)arr);
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	int			len;
	char		buf[BUFF_SIZE + 1];
	static char	*arr[10240];
	char		*tmp;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line)
		return (-1);
	if (!(arr[fd]))
		arr[fd] = ft_strnew(0);
	while (!ft_strchr(arr[fd], '\n'))
	{
		len = read(fd, buf, BUFF_SIZE);
		buf[len] = '\0';
		if (len == 0)
			break ;
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
		if (!(arr[fd]))
			arr[fd] = ft_strnew(0);
	}
	return (ft_getbuf(&arr[fd], line));
}
