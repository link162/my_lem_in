/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/01 15:38:23 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe	*copy_list_pipes(t_pipe *old)
{
	t_pipe *new;
	t_pipe *tmp;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	new->connect = ft_strdup(old->connect);
	new->next = NULL;
	tmp = new;
	while (old->next)
	{
		tmp->next = (t_pipe *)malloc(sizeof(t_pipe));
		tmp->next->connect = ft_strdup(old->next->connect);
		tmp->next->next = NULL;
		old = old->next;
		tmp = tmp->next;
	}
	return (new);
}

void	create_tree(t_lem *lem)
{
	t_room	*new;

	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, lem->start->name))
			if (new->pipe)
			{	
				lem->start->pipe = copy_list_pipes(new->pipe);
				break ;
			}
		new = new->next;
	}
	while (lem->start->pipe)
	{
		ft_printf("$%s\n", lem->start->pipe->connect);
		lem->start->pipe = lem->start->pipe->next;
	}
}
