/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 11:33:11 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 11:24:02 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_way(t_lem *lem)
{
	t_way *help;
	t_way *tmp;

	if (lem->way->done == 0)
	{
		tmp = lem->way->next;
		del_pipes(&lem->way->pipe);
		free(lem->way);
		lem->way = NULL;
		return ;
	}
	tmp = lem->way;
	while (tmp->next)
	{
		if (tmp->next->done == 0)
		{
			help = tmp->next->next;
			del_pipes(&tmp->next->pipe);
			free(tmp->next);
			tmp->next = help;
			return ;
		}
		tmp = tmp->next;
	}
}

int		fill_helper(t_lem *lem, t_pipe *list, t_way *road)
{
	int i;

	i = 0;
	while (list)
	{
		if (!find_in_list_room(lem, road->pipe, list->connect, i))
		{
			if (i > 0)
				clone_way_and_add(lem, road, ft_strdup(list->connect));
			else
			{
				ft_pipe_push_back(&road->pipe, ft_strdup(list->connect));
				road->length++;
				if (!ft_strcmp(list->connect, lem->start->name))
					road->done = 1;
			}
			i++;
		}
		list = list->next;
	}
	return (i);
}

void	fill_way(t_lem *lem)
{
	t_room	*room;
	t_way	*road;
	t_pipe	*name;
	t_pipe	*list;
	int		i;

	road = NULL;
	road = find_way(lem->way);
	if (!road)
		return ;
	name = find_last_room_in_way(road->pipe);
	room = find_room(name->connect, lem->room);
	list = room->pipe;
	i = fill_helper(lem, list, road);
	if (i == 0)
		del_way(lem);
	fill_way(lem);
}

void	sort_ways(t_lem *lem, int x, t_pipe *pipe, t_way *way)
{
	while (x > 0)
	{
		x = 0;
		if (lem->way->length > lem->way->next->length)
		{
			ft_swap(&lem->way->length, &lem->way->next->length);
			pipe = lem->way->next->pipe;
			lem->way->next->pipe = lem->way->pipe;
			lem->way->pipe = pipe;
			x++;
		}
		way = lem->way;
		while (way->next->next)
		{
			if (way->next->length > way->next->next->length)
			{
				ft_swap(&way->next->length, &way->next->next->length);
				pipe = way->next->next->pipe;
				way->next->next->pipe = way->next->pipe;
				way->next->pipe = pipe;
				x++;
			}
			way = way->next;
		}
	}
}

void	find_all_ways(t_lem *lem)
{
	lem->way = create_way();
	lem->way->pipe = ft_create_pipe(ft_strdup(lem->end->name));
	lem->way->length = 0;
	fill_way(lem);
	if (!lem->way)
		error_case(lem);
	if (lem->way->next)
		sort_ways(lem, 1, NULL, NULL);
	lem->count_way = set_numbers(lem->way);
}
