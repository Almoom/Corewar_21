/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljalikak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:45:03 by ljalikak          #+#    #+#             */
/*   Updated: 2019/09/10 19:45:05 by ljalikak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_val	*create_list_valid(char *s)
{
	t_val	*list;
	int		i;

	i = 0;
	if (!(list = (t_val*)ft_memalloc(sizeof(t_val))))
		return (NULL);
	list->line = ft_strdup(s);
	list->error_l = ft_strdup(s);
	while (i < 4)
	{
		if (!(list->arg[i] = (t_ar*)ft_memalloc(sizeof(t_ar))))
			return (NULL);
		i++;
	}
	return (list);
}

t_val	*creator_valid(t_val *head, char *s)
{
	t_val *tmp;
	t_val *list;

	tmp = head;
	list = NULL;
	while (head->next)
		head = head->next;
	list = create_list_valid(s);
	head->next = list;
	list->prev = head;
	return (tmp);
}

void	del_list_valid(t_val **del)
{
	ft_memdel((void**)(&(*del)->line));
	if ((*del)->istxt || (*del)->islbl || (*del)->iscmd)
		ft_memdel((void**)(&(*del)->error_l));
	ft_memdel((void**)(&(*del)->data));
	ft_memdel((void**)(&(*del)->n_lbl));
	ft_memdel((void**)(&(*del)->arg[0]->type));
	ft_memdel((void**)(&(*del)->arg[1]->type));
	ft_memdel((void**)(&(*del)->arg[2]->type));
	ft_memdel((void**)(&(*del)->arg[3]->type));
	ft_memdel((void**)(&(*del)->arg[0]->data));
	ft_memdel((void**)(&(*del)->arg[1]->data));
	ft_memdel((void**)(&(*del)->arg[2]->data));
	ft_memdel((void**)(&(*del)->arg[0]));
	ft_memdel((void**)(&(*del)->arg[1]));
	ft_memdel((void**)(&(*del)->arg[2]));
	ft_memdel((void**)(&(*del)->arg[3]));
	free(*del);
}

void	del_roll_valid(t_val **head)
{
	t_val *tmp;

	if (!(*head))
		return ;
	while ((*head))
	{
		tmp = (*head)->next;
		del_list_valid(head);
		*head = tmp;
	}
}
