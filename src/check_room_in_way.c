/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room_in_way.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 16:10:06 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/19 12:47:30 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*create_way(int id, int length)
{
	t_way *way;

	way = (t_way *)malloc(sizeof(t_way));
	way->id = id;
	way->length = length;
	way->step = NULL;
	way->next = NULL;
	way->done = 0;
	way->ant = 0;
	return (way);
}

void	add_room_to_way(t_way *way, int id)
{
	if (id == 0)
		way->done = 1;
	way->length++;
	while (way->step)
		way = way->step;
	way->step = create_way(id, 0);
}

void	clone_without_last(t_way **queue, t_way *way, int id)
{
	t_way *new;
	t_way *tmp;

	new = create_way(way->id, way->length);
	tmp = new;
	way = way->step;
	while (way->step)
	{
		new->step = create_way(way->id, 0);
		new = new->step;
		way = way->step;
	}
	new->step = create_way(id, 0);
	tmp->next = *queue;
	*queue = tmp;
}

int		is_room_in_way(t_way *way, int id)
{
	while (way)
	{
		if (way->id == id)
			return (1);
		way = way->step;
	}
	return (0);
}

int		check_room_in_way(t_lem *lem, t_way **queue, t_way *way, int id)
{
	t_way	*tmp;
	t_pipe	*pipe;
	int		i;

	i = 0;
	tmp = way;
	pipe = lem->room[id].pipe;
	while (pipe)
	{
		if (!is_room_in_way(way, pipe->id))
		{
			if (i == 0)
			{
				add_room_to_way(way, pipe->id);
				i++;
			}
			else
				clone_without_last(queue, way, pipe->id);
		}
		pipe = pipe->next;
	}
	return (i);
}
