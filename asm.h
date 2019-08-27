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

typedef struct		s_val
{
	struct s_val	*next;
	char			*line;
	char			*data;
	int				is_nm_start;
	int				is_nm_middle;
	int				is_nm_end;
	int				is_cmnt_start;
	int				is_cmnt_middle;
	int				is_cmnt_end;
	int				len;
	int				istxt;
	int				iscmd;
	int				n_cmd;
	int				islbl;
	int				numlbl;
}					t_val;



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
