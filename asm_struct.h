/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:05:19 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:05:27 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCT_H
# define ASM_STRUCT_H

typedef struct		s_ar
{
	char			*type;
	int				dec;
	char			*data;
	int				len;
}					t_ar;

typedef struct		s_val
{
	struct s_val	*next;
	struct s_val	*prev;
	char			*line;
	char			*data;
	char			*n_lbl;
	t_ar			*arg[4];
	int				type;
	char			*error_l;
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
	int				r;
	int				islbl;
}					t_val;

#endif
