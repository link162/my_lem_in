/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:53:12 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/19 15:07:50 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		check_all_way(t_lem *lem, t_way **tmp, t_way **queue, t_way **prev)
{
	t_way	*step;

	if ((*tmp)->done)
	{
//		ft_printf("anouther way done\n");
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
//		ft_printf("delete way\n");
		step = (*tmp)->next;
		del_way(*tmp);
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

	while (*queue)
	{
		tmp = (*queue)->next;
		while (*queue)
		{
			step = (*queue)->step;
			free(*queue);
			*queue = step;
		}
		*queue = tmp;
	}
	return (1);
}

void	print_queue(t_way *queue, t_lem *lem)
{
	t_way *tmp;
	ft_printf("$$$$$$$$$$$$$$$$$$$$$$new$$$$$$$$$$$$$$$$$$$$$$$\n");
	while (queue)
	{
		tmp = queue->next;
		ft_printf("way length %i done %i include \n", queue->length, queue->done);
		while (queue)
		{
			ft_printf("%s\n", lem->room[queue->id].name);
			queue = queue->step;
		}
		queue = tmp;
	}
}

void	cycle_way(t_lem *lem, t_way *queue)
{
	t_way *tmp;
	t_way *prev;

	while (queue)
	{
		ft_printf("stop\n");
		prev = queue;
		if (queue->done)
		{
//			ft_printf("first way done\n");
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
//				if (queue)
					ft_printf("die!!!\n");
			//	print_queue(queue, lem);
			//	if (del_queue(&queue))
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
