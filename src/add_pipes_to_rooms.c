/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/20 14:34:25 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_is_done(t_lem *lem, t_way **tmp, t_way **queue, t_way **prev)
{
	t_way *step;

	if ((*tmp)->done)
	{
		step = (*tmp)->next;
		add_way_in_struct(lem, *tmp);
		if (*tmp == *queue)
			*queue = step;
		else
			(*prev)->next = step;
		*tmp = step;
		return (1);
	}
	return (0);
}

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

void	add_comment(t_pipe **tmp, char *data)
{
	t_pipe *list;

	list = *tmp;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_pipe(data, -1);
	}
	else
		(*tmp) = ft_create_pipe(data, -1);
}
