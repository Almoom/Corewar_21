/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:17:16 by ljalikak          #+#    #+#             */
/*   Updated: 2019/08/25 17:17:17 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	read_file(char *name)
{
	int		fd;
	char	*arr;
	char	*tmp;
	int		flag;

	arr = NULL;
	tmp = NULL;
	flag = 0;
	fd = open(name, O_RDONLY);
	while (fd >= 0 && get_next_line(fd, &arr))
	{
		if (arr[0] != COMMENT_CHAR && arr[0])
		{
			if (arr[ft_strlen(arr) - 1] == ':')
			{
				tmp = ft_strdup(arr);
				flag = 1;
			}
			if (flag != 1)
				ft_putendl(arr);
			if (flag == 1 && arr[ft_strlen(arr) - 1] != ':')
			{
				ft_putstr(tmp);
				free(tmp);
				ft_putendl(arr);
				flag = 0;
			}
		}


		// if (!head && not_comment(arr) && check_realnum(arr))
		// {
		// 	head = create_list_valid(arr);
		// 	head->isnum = 1;
		// }
		// else if (head && not_comment(arr))
		// 	head = creator_valid(head, arr);
		ft_memdel((void**)(&arr));
	}
	ft_memdel((void**)(&arr));
	close(fd);
}

char 	*skip_chars_at_first(char *s, char *chars)
{
	int		begin;
	int		i;
	int		flag;
	char	*tmp;

	begin = 0;
	tmp = NULL;
	while (s[begin])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
		{
			if (s[begin] == chars[i])
			{
				begin++;
				flag = 1;
			}
		}
		if (flag == 0)
			break ;
	}
	tmp = ft_strdup(s + begin);
	free(s);
	return (tmp);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!(s = (char*)malloc(sizeof(*src) * (ft_strlen(src) + 1)))
		|| ft_strlen(src) == 9223372036854775807)
		return (NULL);
	while (src[i] && i <= n)
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char 	*skip_chars_from_end(char *s, char *chars)
{
	int		end;
	int		i;
	int		flag;
	char	*tmp;

	end = ft_strlen(s) - 1;
	tmp = NULL;
	while (s[end])
	{
		i = -1;
		flag = 0;
		while (chars[++i])
		{
			if (s[end] == chars[i])
			{
				end--;
				flag = 1;
			}
		}
		if (flag == 0)
			break ;
	}
	tmp = ft_strndup(s, end);
	free(s);
	return (tmp);
}

int		main(int ac, char **av)
{
	char *s;

	s = skip_chars_at_first(ft_strdup("  		  001  		  "), " 	");
	printf("%s\n", s);
	free(s);
	s = skip_chars_from_end(ft_strdup("  		  001  		  "), " 	");
	printf("%s\n", s);
	free(s);
	// if (ac == 2 && !ft_strcmp(av[1] + ft_strlen(av[1]) - 2, ".s"))
	// 	read_file(av[1]);
	// else
	// 	ft_putendl("Неверное количество файлов или файл не с расширением .s");
	return (0);
}
