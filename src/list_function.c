/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 10:33:15 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*find_nbr_way(t_way *way, int nbrway)
{
	while (way)
	{
		if (way->number == nbrway)
			return (way);
		way = way->next;
	}
	return (NULL);
}

int		find_in_list_room(t_lem *lem, t_pipe *pipe, char *str, int i)
{
	t_pipe *tmp;
	t_pipe *last;
	t_room *in;
	t_room *out;

	if (i > 0)
		return (find_in_list_room_last(lem, pipe, str));
	tmp = pipe;
	while (tmp)
	{
		last = tmp;
		if (!ft_strcmp(tmp->connect, str))
			return (1);
		tmp = tmp->next;
	}
	in = find_room(last->connect, lem->room);
	out = find_room(str, lem->room);
	if (in->index < out->index)
		return (1);
	return (0);
}

t_room	*ft_create_room(char *data, int x, int y)
{
	t_room	*list;

	list = NULL;
	list = (t_room *)malloc(sizeof(t_room));
	if (list)
	{
		list->name = data;
		list->x = x;
		list->y = y;
		list->next = NULL;
		list->pipe = NULL;
		list->index = -1;
		list->put = 0;
	}
	return (list);
}

t_pipe	*find_last_room_in_way(t_pipe *pipe)
{
	t_pipe	*tmp;

	tmp = pipe;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	ft_room_push_back(t_lem *lem, char *data, int x, int y)
{
	t_room	*list;

	list = lem->room;
	if (list)
	{
		if (list->x == x && list->y == y)
			error_case(lem);
		if (!ft_strcmp(data, list->name))
			error_case(lem);
		while (list->next)
		{
			if (list->next->x == x && list->next->y == y)
				error_case(lem);
			if (!ft_strcmp(data, list->next->name))
				error_case(lem);
			list = list->next;
		}
		list->next = ft_create_room(data, x, y);
	}
	else
		lem->room = ft_create_room(data, x, y);
}
