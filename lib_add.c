/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_add.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:03:18 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:03:21 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_get_next_file(const int fd, char **line)
{
	int			len;
	char		buf[BUFF_SIZE + 1];
	static char	*arr[10240];
	char		*tmp;

	if (fd < 0 || read(fd, buf, 0) < 0 || !line || fd > 10240)
		return (-1);
	len = ((arr[fd] == 0) ? 0 : 1);
	if (!(arr[fd]))
		arr[fd] = ft_strnew(0);
	while ((len = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[len] = '\0';
		tmp = ft_strjoin(arr[fd], buf);
		free(arr[fd]);
		arr[fd] = tmp;
	}
	*line = arr[fd];
	arr[fd] = NULL;
	if ((*line)[0] == '\0')
		return (0);
	return (1);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	s = ft_strnew(n);
	while (src[i] && i < n)
	{
		s[i] = src[i];
		i++;
	}
	return (s);
}

void	del_split(char ***str)
{
	int		i;
	char	**s;

	s = *str;
	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	*str = NULL;
}

int		count_chars(char *s, int ch)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ch)
			count++;
		i++;
	}
	return (count);
}

int		split_len(char **s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
