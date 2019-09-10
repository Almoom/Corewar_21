/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_16.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:52:26 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/08 18:52:29 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strnrev_free(char *s, int count, int flag)
{
	char	*t;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	k = count - i;
	t = ft_strnew(count + 1);
	ft_memset(t, '0', count);
	while (k < count)
	{
		t[k] = s[i - 1];
		k++;
		i--;
	}
	flag == 1 ? free(s) : 0;
	return (t);
}

char	*ft_itoa_16(int n, int count)
{
	char *s;
	char arr[2] = {0, 0};
	unsigned int num;

	num = (unsigned int)n;
	s = ft_strnew(0);
	while(num > 0)
	{
		arr[0] = num % 16 + (num % 16 > 9 ? 'a' - 10 : '0');
		s = ft_strjoin_free(s, arr, 1, 0);
		num /= 16;
	}
	return (s = ft_strnrev_free(s, count, 1));
}
