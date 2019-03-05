/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:19:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/05 13:34:43 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		find_connect_room(t_lem *lem, char *line)//
{
	t_room *room;

	room = lem->room;
	while (room)
	{
		if (!ft_strncmp(room->name, line, ft_strlen(room->name)))
			return (ft_strlen(room->name));
		room = room->next;
	}
	error_case(lem);
	return (0);
}

t_pipe	*ft_create_pipe(char *data, int id)
{
	t_pipe	*list;

	list = NULL;
	list = malloc(sizeof(t_pipe));
	if (list)
	{
		list->id = id;
		list->connect = data;
		list->next = NULL;
	}
	return (list);
}

int		ft_pipe_push_back(t_pipe **tmp, char *data)//
{
	t_pipe *list;

	list = *tmp;
	if (list)
	{
		if (!ft_strcmp(data, list->connect))
			return (1);
		while (list->next)
		{
			if (!ft_strcmp(data, list->next->connect))
				return (1);
			list = list->next;
		}
		list->next = ft_create_pipe(data, -1);
	}
	else
		(*tmp) = ft_create_pipe(data, -1);
	return (0);
}

int		add_pipe_to_struct(t_lem *lem, char *from, char *to)//
{
	t_room *new;

	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, from))
		{
			if (ft_pipe_push_back(&new->pipe, to))
				return (1);
			return (0);
		}
		new = new->next;
	}
	if (!new)
		error_case(lem);
	return (0);
}

void	check_pipe(char *line, t_lem *lem)//
{
	int		i;
	char	*from;
	char	*to;

	i = 0;
	ft_pipe_push_back(&lem->pipes, ft_strdup(line));
	i = find_connect_room(lem, line);
	from = (char *)malloc(sizeof(char) * (i + 1));
	ft_bzero(from, i + 1);
	ft_strncpy(from, line, i);
	line = line + i + 1;
	i = 0;
	while (line[i])
		i++;
	to = (char *)malloc(sizeof(char) * (i + 1));
	ft_bzero(to, i + 1);
	ft_strncpy(to, line, i);
	if (add_pipe_to_struct(lem, from, to) || add_pipe_to_struct(lem, to, from))
		error_case(lem);
}
