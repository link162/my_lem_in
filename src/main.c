/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/05 16:27:23 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_init(t_lem *lem)
{
	lem->index = -1;
	lem->ants = 0;
	lem->rooms = 0;
	lem->ways = 1;
	lem->way = NULL;
	lem->pipes = NULL;
	lem->room = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->groups = 0;
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

void	print_ways(t_lem *lem)
{
	t_way *tmp;
	t_way *step;
	t_group *group;
	int i = 0;

	group = lem->group;
	ft_printf("global index %i\n", lem->index);
	while (i < lem->groups)
	{
		ft_printf("group %i, index %i include ways\n", i, lem->group[i].index);
		tmp = lem->group[i].way;
		while (tmp)
		{
			ft_printf("way length %i - ", tmp->length);
			step = tmp;
			while (step)
			{
//				ft_printf("%s, ", lem->room[step->id].name);
				step = step->step;
			}
			ft_putchar('\n');
			tmp = tmp->next;
		}
		i++;
	}
}

void	print_rooms(t_lem *lem)
{
	int i = -1;
	t_pipe *pipe;

	while (++i < lem->rooms)
	{
		ft_printf("room \"%s\" id %i index %i connect to ", lem->room[i].name, i, lem->room[i].index);
		pipe = lem->room[i].pipe;
		while (pipe)
		{
			ft_printf("%s ", lem->room[pipe->id].name);
			pipe = pipe->next;
		}
		ft_putchar('\n');
	}
}

int		main(void)
{
	t_lem	lem;

	map_init(&lem);
	read_data(&lem, 0);
	add_pipes_to_rooms(&lem);
	check_errors(&lem);
	convert_to_arr(&lem);
//	print_rooms(&lem);
	set_index(&lem);
	print_rooms(&lem);
	find_ways(&lem);
	print_ways(&lem);
//	system("leaks lem-in");
}
