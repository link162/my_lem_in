/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 15:45:01 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/18 16:04:56 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_room(t_room *room)
{
	int x;

	x = 0;
	while (room)
	{
		room = room->next;
		x++;
	}
	return (x);
}

int		find_room_id(char *str, t_lem *lem)
{
	int i;

	i = 0;
	while (i < lem->rooms)
	{
		if (!ft_strcmp(str, lem->room[i].name))
			return (i);
		i++;
	}
	error_case(lem);
	return (-1);
}

t_pipe	*add_pipes_in_nbr(t_lem *lem, char *str, t_room *list)
{
	t_pipe *pipe;

	while (list)
	{
		if (!(ft_strcmp(list->name, str)))
			break ;
		list = list->next;
	}
	pipe = list->pipe;
	while (pipe)
	{
		pipe->id = find_room_id(pipe->connect, lem);
		pipe = pipe->next;
	}
	return (list->pipe);
}

void	copy_rooms_to_arr(t_lem *lem, t_room *room, int i)
{
	t_room	*tmp;
	int		z;

	tmp = room;
	while (room)
	{
		if (!ft_strcmp(room->name, lem->start->name) ||
				!ft_strcmp(room->name, lem->end->name))
		{
			z = !ft_strcmp(room->name, lem->start->name) ? 0 : 1;
			lem->room[z].name = room->name;
			lem->room[z].x = room->x;
			lem->room[z].y = room->y;
		}
		else
		{
			lem->room[i].name = room->name;
			lem->room[i].x = room->x;
			lem->room[i++].y = room->y;
		}
		room = room->next;
	}
	i = -1;
	while (++i < lem->rooms)
		lem->room[i].pipe = add_pipes_in_nbr(lem, lem->room[i].name, tmp);
}

void	convert_to_arr(t_lem *lem)
{
	t_room	*room;
	t_room	*tmp;

	room = lem->room;
	lem->rooms = count_room(room);
	lem->room = (t_room *)malloc(sizeof(t_room) * lem->rooms);
	copy_rooms_to_arr(lem, room, 2);
	while (room)
	{
		tmp = room->next;
		free(room);
		room = tmp;
	}
}
