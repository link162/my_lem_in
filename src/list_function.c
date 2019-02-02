/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/02 13:51:13 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_create_room(char *data)
{
	t_room	*list;

	list = NULL;
	list = (t_room *)malloc(sizeof(t_room));
	if (list)
	{
		list->name = data;
		list->next = NULL;
		list->pipe = NULL;
		list->index = -1;
		list->put = 0;
	}
	return (list);
}

t_pipe	*ft_create_pipe(char *data)
{
	t_pipe	*list;

	list = NULL;
	list = malloc(sizeof(t_pipe));
	if (list)
	{
		list->connect = data;
		list->next = NULL;
	}
	return (list);
}

void	ft_pipe_push_back(t_room *room, char *data)
{
	t_pipe	*list;

	list = room->pipe;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_pipe(data);
	}
	else
		room->pipe = ft_create_pipe(data);
}

void	ft_room_push_back(t_lem *lem, char *data)
{
	t_room	*list;

	list = lem->room;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = ft_create_room(data);
	}
	else
		lem->room = ft_create_room(data);
}
