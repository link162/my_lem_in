/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/01 14:33:03 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*ft_create_room(char *data)
{
	t_room	*list;

	list = NULL;
	list = malloc(sizeof(t_room));
	if (list)
	{
		list->name = data;
		list->next = NULL;
		list->pipe = NULL;
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
/*
void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list	*list;

	if (*begin_list)
	{
		list = ft_create_elem(data);
		list.next = *begin_list;
		*begin_list = list;
	}
	else
		*begin_list = ft_create_elem(data);
}*/
