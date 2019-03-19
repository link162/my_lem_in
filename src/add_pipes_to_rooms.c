/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/18 15:12:24 by ybuhai           ###   ########.fr       */
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

void	add_pipes_to_rooms(t_lem *lem)
{
	t_room	*new;

	if (!lem->start || !lem->end)
		error_case(lem);
	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, lem->start->name) && new->pipe)
		{
			lem->start->pipe = copy_list_pipes(new->pipe);
			break ;
		}
		new = new->next;
	}
	new = lem->room;
	while (new)
	{
		if (!strcmp(new->name, lem->end->name) && new->pipe)
		{
			lem->end->pipe = copy_list_pipes(new->pipe);
			break ;
		}
		new = new->next;
	}
}
