/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/17 18:49:20 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_init(t_lem *lem)
{
	lem->index = -1;
	lem->ants = 0;
	lem->rooms = 0;
	lem->ways = 0;
	lem->way = NULL;
	lem->pipes = NULL;
	lem->room = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->groups = 0;
	lem->big_group = NULL;
	lem->group = NULL;
}

void	check_errors(t_lem *lem)
{
	t_room *room;

	if (lem->ants < 1)
		error_case(lem);
	if (!lem->start)
		error_case(lem);
	if (!lem->end)
		error_case(lem);
	room = lem->room;
	while (room)
	{
		if (!room->pipe)
			error_case(lem);
		room = room->next;
	}
}

void	clear_groups(t_lem *lem)
{
	int		i;
	t_way	*way;
	t_way	*tmp;

	i = 0;
	while (i < lem->groups)
	{
		while (lem->group[i].way)
		{
			way = lem->group[i].way->next;
			while (lem->group[i].way)
			{
				tmp = lem->group[i].way->step;
				free(lem->group[i].way);
				lem->group[i].way = tmp;
			}
			lem->group[i].way = way;
		}
		i++;
	}
	free(lem->group);
}

int		main(void)
{
	t_lem	lem;
	int		i;

	i = -1;
	map_init(&lem);
	read_data(&lem, 0);
	add_pipes_to_rooms(&lem);
	check_errors(&lem);
	convert_to_arr(&lem);
	algorithm_big(&lem);
	if (lem.ways < GROUP)
	{
		find_ways(&lem);
		if (lem.index > lem.big_group->index)
			print_lem(&lem, lem.big_group);
		else
			while (++i < lem.groups)
				if (lem.group[i].index == lem.index)
					print_lem(&lem, &lem.group[i]);
	}
	else
		print_lem(&lem, lem.group);
	system("leaks lem-in");
}
