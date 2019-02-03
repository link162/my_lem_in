/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:08:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/03 19:39:35 by ybuhai           ###   ########.fr       */
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

void	ft_pipe_push_back(t_pipe **tmp, char *data)
{
	t_pipe	*list;

	list = *tmp;
	if (list)
	{
		while (list->next)
		{
			if (!ft_strcmp(data, list->connect))
			{
				ft_printf("find a same pipe!\n");
				exit (1);
			}
			list = list->next;
		}
		list->next = ft_create_pipe(data);
	}
	else
		(*tmp) = ft_create_pipe(data);
}

void	ft_room_push_back(t_lem *lem, char *data)
{
	t_room	*list;

	list = lem->room;
	ft_printf("%s\n", data);
	if (list)
	{
		while (list->next)
		{
			if (!ft_strcmp(data, list->name))
			{
				ft_printf("find a same rooms!\n");//dont work
				exit (1);
			}
			list = list->next;
		}
		list->next = ft_create_room(data);
	}
	else
		lem->room = ft_create_room(data);
}
