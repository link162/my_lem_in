/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_groups_ways.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:41:00 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 12:53:07 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_shortest_way_in_group(t_lem *lem)
{
	int		less;
	int		group;
	t_way	*way;

	less = lem->way->length;
	way = find_nbr_way(lem->way, lem->group->nbr_way);
	group = way->length;
	if (less == group)
		return (0);
	return (1);
}

void	choose_group_or_shortway(t_lem *lem)
{
	int val_short;
	int val_group;

	val_short = lem->way->length + lem->ants - 1;
	val_group = (count_way_length(lem) + lem->ants) / lem->ways_in_group +
		lem->ants % lem->ways_in_group - 1;
	if (val_group <= val_short)
		choose_group(lem);
	else
		choose_short_way(lem);
}

t_road	*make_road(t_pipe *pipe)
{
	t_road *new;
	t_road *ret;

	new = (t_road *)malloc(sizeof(t_road));
	new->ant = 0;
	new->room = NULL;
	new->next = NULL;
	new->name = pipe->connect;
	ret = new;
	pipe = pipe->next;
	while (pipe)
	{
		new->room = (t_road *)malloc(sizeof(t_road));
		new->room->room = NULL;
		new->room->next = NULL;
		new->room->ant = 0;
		new->room->name = pipe->connect;
		pipe = pipe->next;
		new = new->room;
	}
	return (ret);
}

int		find_road_index(t_road *road, int i)
{
	int	res;

	res = 0;
	while (road->next)
	{
		res += i - road->length;
		road = road->next;
	}
	return (res);
}

t_road	*make_group_road(t_lem *lem)
{
	t_road	*road;
	t_road	*tmp;
	t_group	*group;
	t_way	*way;

	group = lem->group->next;
	way = find_nbr_way(lem->way, lem->group->nbr_way);
	road = make_road(way->pipe);
	road->index = 0;
	road->length = way->length;
	tmp = road;
	while (group)
	{
		way = find_nbr_way(lem->way, group->nbr_way);
		road->next = make_road(way->pipe);
		road->next->next = NULL;
		road->next->length = way->length;
		road->next->index = find_road_index(tmp, way->length);
		group = group->next;
		road = road->next;
	}
	return (tmp);
}
