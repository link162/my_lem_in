/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 19:09:23 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

int		ft_pipe_push_back(t_pipe **tmp, char *data)
{
	t_pipe	*list;

	list = *tmp;
	if (list)
	{
		if (!ft_strcmp(data, list->connect))
		{
			ft_printf("ERROR\n");
			return (1);
		}
		while (list->next)
		{
			if (!ft_strcmp(data, list->next->connect))
			{
				ft_printf("ERROR\n");
				return (1);
			}
			list = list->next;
		}
		list->next = ft_create_pipe(data);
	}
	else
		(*tmp) = ft_create_pipe(data);
	return (0);
}

void	ft_room_push_back(t_lem *lem, char *data, int x, int y)
{
	t_room	*list;

	list = lem->room;
	if (list)
	{
		if (list->x == x && list->y == y)
		{
			ft_printf("ERROR\n");
			clear_data(lem);
		}
		if (!ft_strcmp(data, list->name))
		{
			ft_printf("ERROR\n");
			clear_data(lem);
		}
		while (list->next)
		{
			if (list->next->x == x && list->next->y == y)
			{
				ft_printf("ERROR\n");
				clear_data(lem);
			}
			if (!ft_strcmp(data, list->next->name))
			{
				ft_printf("ERROR\n");
				clear_data(lem);
			}
			list = list->next;
		}
		list->next = ft_create_room(data, x, y);
	}
	else
		lem->room = ft_create_room(data, x, y);
}
