/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/02 17:45:46 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_init(t_lem *lem)
{
	lem->ants = 0;
	lem->rooms = 0;
	lem->ways = 1;
	lem->way = NULL;
	lem->pipes = NULL;
	lem->room = NULL;
	lem->start = NULL;
	lem->end = NULL;
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

	tmp = lem->way;
	while (tmp)
	{
		ft_printf("way %i length %i, ", tmp->number, tmp->length);
//		step = tmp;
///		while (step)
//		{
//			ft_printf("%i ", step->id);
//			step = step->step;
//		}
		tmp = tmp->next;
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
	find_ways(&lem);
	print_ways(&lem);
	system("leaks lem-in");
}
