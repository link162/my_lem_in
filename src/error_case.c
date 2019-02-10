/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:22:47 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 12:47:00 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		set_numbers(t_way *way)
{
	int x;

	x = 0;
	while (way)
	{
		way->number = x++;
		way = way->next;
	}
	return (x);
}

void	index_helper(t_lem *c, t_pipe *way, t_room *list, t_room *target)
{
	t_room *t;

	while (way)
	{
		t = list;
		while (t)
		{
			if (!ft_strcmp(t->name, way->connect))
				if (t->index < 0 || t->index > target->index + 1)
				{
					t->index = target->index + 1;
					if (t->put == 0)
					{
						ft_room_push_back(c, ft_strdup(t->name), t->x, t->y);
						t->put = 2;
					}
				}
			t = t->next;
		}
		way = way->next;
	}
}

void	free_start_end(t_lem *lem)
{
	t_way *way;

	free(lem->start->name);
	del_pipes(&lem->start->pipe);
	free(lem->start);
	free(lem->end->name);
	del_pipes(&lem->end->pipe);
	free(lem->end);
	while (lem->way)
	{
		del_pipes(&lem->way->pipe);
		way = lem->way->next;
		free(lem->way);
		lem->way = way;
	}
}

void	clear_data(t_lem *lem)
{
	t_group *group;
	t_room	*room;

	del_pipes(&lem->pipes);
	while (lem->group)
	{
		group = lem->group->next;
		free(lem->group);
		lem->group = group;
	}
	while (lem->room)
	{
		room = lem->room->next;
		free(lem->room->name);
		del_pipes(&lem->room->pipe);
		free(lem->room);
		lem->room = room;
	}
	free_start_end(lem);
	get_next_line(-5, NULL);
}

void	error_case(t_lem *lem)
{
	ft_printf("ERROR\n");
	clear_data(lem);
}
