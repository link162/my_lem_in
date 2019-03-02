/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:53:12 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/02 17:45:18 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_way_in_struct(t_lem *lem, t_way *tmp)
{
	t_way *way;
	static int i;

	tmp->number = i++;
	tmp->next = NULL;
	way = lem->way;
	if (!lem->way)
		lem->way = tmp;
	else
	{
		while (way->next)
			way = way->next;
		way->next = tmp;
	}
}

void	del_way(t_way *way)
{
	t_way *tmp;

	while (way)
	{
		tmp = way->step;
		free(way);
		way = tmp;
	}
}

void	cycle_way(t_lem *lem, t_way *queue)
{
	t_way *tmp;
	t_way *step;
	t_way *prev;

	while (queue)
	{
		if (queue->done)
		{
			tmp = queue->next;
			add_way_in_struct(lem, queue);
			queue = tmp;
			continue ;
		}
		tmp = queue;
		while (tmp)
		{
			
			if (tmp->done)
			{
				step = tmp->next;
				add_way_in_struct(lem, tmp);
				prev->next = step;
				tmp = step;
				continue ;
			}
			step = tmp;
			while (step->step)
				step = step->step;
			if (!check_room_in_way(lem, &queue, tmp, step->id))
			{
				if (tmp == queue)
				{
					step = tmp->next;
					del_way(tmp);
					queue = step;
				}
				else
				{
					step = tmp->next;
					del_way(tmp);
					prev->next = step;
				}
				tmp = step;
				continue ;
			}
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	find_ways(t_lem *lem)
{
	t_way *new;

	new = create_way(1, 0);
	cycle_way(lem, new);
}
