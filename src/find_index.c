/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_index.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:37:39 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 22:50:28 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*find_room(char *str, t_room *list)
{
	t_room *tmp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strcmp(str, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	remove_first_list(t_lem *clone)
{
	t_room *tmp;

	tmp = clone->room->next;
	free(clone->room->name);
	free(clone->room);
	clone->room = tmp;
}

int		check_index(t_lem *clone, t_room *list)
{
	t_room	*target;
	t_room	*tmp;
	t_pipe	*way;

	if (!clone->room)
		return (1);
	target = find_room(clone->room->name, list);
	if (!target)
		return (0);
	way = target->pipe;
	while (way)
	{
		tmp = list;
		while (tmp)
		{
			if (!ft_strcmp(tmp->name, way->connect))
				if (tmp->index < 0 || tmp->index > target->index + 1)
				{
					tmp->index = target->index + 1;
					if (tmp->put == 0)
					{
						ft_room_push_back(clone, ft_strdup(tmp->name), tmp->x, tmp->y);
						tmp->put = 2;
					}
				}
			tmp = tmp->next;
		}
		way = way->next;
	}
	remove_first_list(clone);
	return (check_index(clone, list));
}

void	set_start_index(t_lem *lem)
{
	t_room *tmp;

	tmp = lem->room;
	while (tmp)
	{
		if (!ft_strcmp(lem->start->name, tmp->name))
		{
			tmp->put = 2;
			tmp->index = 0;
		}
		else if (!ft_strcmp(lem->end->name, tmp->name))
			tmp->put = 2;
		tmp = tmp->next;
	}
}

void	find_index(t_lem *lem)
{
	t_lem clone;

	lem->start->index = 0;
	set_start_index(lem);
	clone.room = ft_create_room(ft_strdup(lem->start->name),
			lem->start->x, lem->start->y);
	if (!check_index(&clone, lem->room))
		error_case(lem);
}
