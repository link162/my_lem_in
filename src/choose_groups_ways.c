/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_groups_ways.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 17:41:00 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/07 17:08:24 by ybuhai           ###   ########.fr       */
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

int		count_way_length(t_lem *lem)
{
	int x;
	t_group	*group;
	t_way	*way;

	group = lem->group;
	x = 0;
	while (group)
	{
		way = find_nbr_way(lem->way, group->nbr_way);
		x += way->length;
		group = group->next;
	}
	return (x);
}

void	choose_group_or_shortway(t_lem *lem)
{
	int val_short;
	int val_group;

	val_short = lem->way->length + lem->ants - 1;
	val_group = (count_way_length(lem) + lem->ants) / lem->ways_in_group + lem->ants % lem->ways_in_group - 1;
	if (val_group < val_short)
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

t_road	*make_group_road(t_lem *lem)
{
	t_road	*road;
	t_road	*tmp;
	t_group	*group;
	t_way	*way;

	group = lem->group->next;
	way = find_nbr_way(lem->way, lem->group->nbr_way);
	road = make_road(way->pipe);
	tmp = road;
	while (group)
	{
		way = find_nbr_way(lem->way, group->nbr_way);
		road->next = make_road(way->pipe);
		group = group->next;
		road = road->next;
	}
	return (tmp);
}

void	choose_group(t_lem *lem)
{
	t_road	*tmp;
	t_road	*road;
	int		a;
	int		count;

	a = lem->ants;
	count = (count_way_length(lem) + lem->ants) / lem->ways_in_group + lem->ants % lem->ways_in_group - 1;
	road = make_group_road(lem);
	while (count)
	{
		tmp = road;
		while (tmp)
		{
			if (tmp->room->ant > 0 && ft_strcmp(tmp->room->name, lem->start->name))
			{
				ft_printf("L%i-%s, ", tmp->room->ant, tmp->name);
				tmp->ant = tmp->room->ant;
				tmp->room->ant = 0;
			}
			else if (!ft_strcmp(tmp->room->name, lem->start->name) && a)
			{

				ft_printf("L%i-%s, ", lem->ants - a + 1, tmp->name);
				tmp->ant = lem->ants - a--  + 1;
			}
			tmp = tmp->room;
		}
	}
}

void	choose_short_way(t_lem *lem)
{
	int		a;
	int		steps;
	t_road	*road;
	t_road	*tmp;

	a = lem->ants;
	road = make_road(lem->way->pipe);
	steps = lem->way->length + lem->ants - 1;
	while (steps)
	{
		tmp = road;
		while (tmp->room)
		{
			if (tmp->room->ant > 0 && ft_strcmp(tmp->room->name, lem->start->name))
			{
				ft_printf("L%i-%s, ", tmp->room->ant, tmp->name);
				tmp->ant = tmp->room->ant;
				tmp->room->ant = 0;
			}
			else if (!ft_strcmp(tmp->room->name, lem->start->name) && a)
			{
				ft_printf("L%i-%s, ", lem->ants - a + 1, tmp->name);
				tmp->ant = lem->ants - a--  + 1;
			}
			tmp = tmp->room;
		}
		steps--;
		ft_putchar('\n');
	}
}