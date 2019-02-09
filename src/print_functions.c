/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:12:51 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 23:18:22 by ybuhai           ###   ########.fr       */
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
				ft_printf("L%i-%s ", tmp->room->ant, tmp->name);
				tmp->ant = tmp->room->ant;
				tmp->room->ant = 0;
			}
			else if (!ft_strcmp(tmp->room->name, lem->start->name) && a)
			{
				ft_printf("L%i-%s ", lem->ants - a + 1, tmp->name);
				tmp->ant = lem->ants - a--  + 1;
			}
			tmp = tmp->room;
		}
		steps--;
		ft_putchar('\n');
	}
}

void	choose_group(t_lem *lem)
{
	t_road	*tmp;
	t_road	*road;
	t_road	*row;
	int		a;
	int		count;
	int		index;

	a = lem->ants;
	count = (count_way_length(lem) + lem->ants) / lem->ways_in_group + lem->ants % lem->ways_in_group - 1;
	road = make_group_road(lem);
	while (count--)
	{
		tmp = road;
		while (tmp)
		{
			row = tmp;
			index = row->index;
			while (row->room)
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
				row = row->room;
			}
			tmp = tmp->next;
		}
		ft_putchar('\n');
	}
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
