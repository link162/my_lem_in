/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:53:12 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/19 12:49:49 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_way(t_way **way)
{
	t_way *tmp;

	while (*way)
	{
		tmp = (*way)->step;
		free(*way);
		*way = tmp;
	}
}

int		check_all_way(t_lem *lem, t_way **tmp, t_way **queue, t_way **prev)
{
	t_way	*step;

	if ((*tmp)->done)
	{
		step = (*tmp)->next;
		add_way_in_struct(lem, *tmp);
		(*prev)->next = step;
		(*tmp) = step;
		return (1);
	}
	step = *tmp;
	while (step->step)
		step = step->step;
	if (!check_room_in_way(lem, queue, *tmp, step->id))
	{
		step = (*tmp)->next;
		del_way(tmp);
		if (*tmp == *queue)
			*queue = step;
		else
			(*prev)->next = step;
		*tmp = step;
		return (1);
	}
	return (0);
}

int		del_queue(t_way **queue)
{
	t_way *tmp;
	t_way *step;
	t_way *way;

	while (*queue)
	{
		tmp = (*queue)->next;
		step = (*queue)->step;
		while (step)
		{
			way = step->step;
			free(step);
			step = way;
		}
		free(*queue);
		*queue = tmp;
	}
	return (1);
}

void	cycle_way(t_lem *lem, t_way *queue)
{
	t_way *tmp;
	t_way *prev;

	while (queue)
	{
		prev = queue;
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
			if (lem->index > 0 && tmp->length >= lem->index)
			{
				if (del_queue(&queue))
					return ;
			}
			if (check_all_way(lem, &tmp, &queue, &prev))
				continue ;
			prev = tmp;
			tmp = tmp->next;
		}
	}
}


void	find_ways(t_lem *lem)
{
	t_way *new;

	clear_index_room(lem);
	lem->way = NULL;
	lem->big_group = lem->group;
	lem->group = NULL;
	new = create_way(1, 0);
	cycle_way(lem, new);
}
