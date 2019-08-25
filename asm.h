/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/25 17:18:23 by ljalikak          #+#    #+#             */
/*   Updated: 2019/08/25 17:18:25 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"
# define TRUE 1
# define FALSE 0

typedef struct		s_read
{
	struct s_read	*next;
	char			*line;
	char			*name;
	char			*x_y;
	char			*name1;
	char			*name2;
	int				isnum;
	int				isstart;
	int				isend;
	int				isxy;
	int				isedge;
}					t_read;



/*
**	main.c
*/



/*
**	list_val.c
*/



/*
**	check_comment_and_realnum.c
*/



/*
**	check_xy_and_edge.c
*/



/*
**	splits.c
*/



/*
**	duplicate.c
*/



/*
**	list_const.c
*/



#endif
