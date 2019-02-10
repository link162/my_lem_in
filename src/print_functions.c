/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:12:51 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 12:48:26 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_field(t_lem *lem)
{
	t_room	*room;
	t_pipe	*pipe;

	ft_printf("%i\n", lem->ants);
	ft_printf("##start\n%s %i %i\n", lem->start->name,
			lem->start->x, lem->start->y);
	ft_printf("##end\n%s %i %i\n", lem->end->name, lem->end->x, lem->end->y);
	room = lem->room;
	while (room)
	{
		if (ft_strcmp(room->name, lem->start->name) &&
				ft_strcmp(room->name, lem->end->name))
			ft_printf("%s %i %i\n", room->name, room->x, room->y);
		room = room->next;
	}
	pipe = lem->pipes;
	while (pipe)
	{
		ft_printf("%s\n", pipe->connect);
		pipe = pipe->next;
	}
	ft_putchar('\n');
}

int		next_room_if(t_lem *lem, t_road *row, int a, int index)
{
	if (row->room->ant > 0 && ft_strcmp(row->room->name, lem->start->name))
	{
		ft_printf("L%i-%s ", row->room->ant, row->name);
		row->ant = row->room->ant;
		row->room->ant = 0;
	}
	else if (!ft_strcmp(row->room->name, lem->start->name) && a)
	{
		if (a > index)
		{
			ft_printf("L%i-%s ", lem->ants - a + 1, row->name);
			row->ant = lem->ants - a-- + 1;
		}
	}
	return (a);
}

void	group_helper(t_lem *lem, int count, int a, t_road *road)
{
	t_road	*tmp;
	t_road	*row;
	int		index;

	while (count--)
	{
		tmp = road;
		while (tmp)
		{
			row = tmp;
			index = row->index;
			while (row->room)
			{
				a = next_room_if(lem, row, a, index);
				row = row->room;
			}
			tmp = tmp->next;
		}
		ft_putchar('\n');
	}
}

void	choose_group(t_lem *lem)
{
	t_road	*road;
	int		a;
	int		count;

	a = lem->ants;
	count = (count_way_length(lem) + lem->ants) / lem->ways_in_group +
		lem->ants % lem->ways_in_group - 1;
	road = make_group_road(lem);
	group_helper(lem, count, a, road);
	free_road(road);
}

int		count_way_length(t_lem *lem)
{
	int		x;
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
