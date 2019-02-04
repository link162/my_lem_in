/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 11:33:11 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/03 17:40:02 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_way	*create_way(void)
{
	t_way *new;

	new = (t_way *)malloc(sizeof(t_way));
	new->length = 0;
	new->done = 0;
	new->pipe = NULL;
	new->next = NULL;
	return (new);
}

t_way	*find_way(t_way *way)
{
	t_way *tmp;

	tmp = way;
	while (tmp)
	{
		if (tmp->done == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_pipe	*find_last_room_in_way(t_pipe *pipe)
{
	t_pipe	*tmp;

	tmp = pipe;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	clone_way_and_add(t_way *way, t_way *obj, char *str, int nbr)
{
	t_way	*start;
	t_pipe	*pipe;

	start = way;
	while (start->next)
		start = start->next;
	start->next = create_way();
	start->next->length = nbr;
	start->next->pipe = copy_list_pipes(obj->pipe);
	pipe = start->next->pipe;
	while (pipe->next->next)
		pipe = pipe->next;
	free(pipe->next->connect);
	free(pipe->next);
	pipe->next = NULL;
	ft_pipe_push_back(&start->next->pipe, str);
}

int		find_in_list_room(t_pipe *pipe, char *str)
{
	t_pipe *tmp;

	tmp = pipe;
	while (tmp)
	{
		if (!ft_strcmp(tmp->connect, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	del_pipes(t_pipe **pipes)
{
	t_pipe *tmp;
	t_pipe *help;

	tmp = *pipes;
	while (tmp)
	{
		help = tmp->next;
		free(tmp->connect);
		free(tmp);
		tmp = help;
	}
	*pipes = NULL;
}

void	del_way(t_lem *lem)
{
	t_way *help;
	t_way *tmp;

	if (lem->way->done == 0)
	{
		tmp = lem->way->next;
		del_pipes(&lem->way->pipe);
		free(lem->way);
		lem->way = NULL;
		return ;
	}
	tmp = lem->way;
	while (tmp->next)
	{
		if (tmp->next->done == 0)
		{
			help = tmp->next->next;
			del_pipes(&tmp->next->pipe);
			free(tmp->next);
			tmp->next = help;
			return ;
		}
		tmp = tmp->next;
	}
}

void	fill_way(t_lem *lem)
{
	t_room	*room;
	t_way	*road;
	t_pipe	*name;
	t_pipe	*list;
	int		i;

	i = 0;
	road = NULL;
	road = find_way(lem->way);
	if (!road)
		return ;
	name = find_last_room_in_way(road->pipe);
	room = find_room(name->connect, lem->room);
	list = room->pipe;
	while (list)
	{
		if (!find_in_list_room(road->pipe, list->connect))
		{
			if (i > 0)
				clone_way_and_add(lem->way, road, ft_strdup(list->connect), road->length);
			else
			{
				ft_pipe_push_back(&road->pipe, ft_strdup(list->connect));
				road->length++;
			}
			if (!ft_strcmp(list->connect, lem->start->name))
				road->done = 1;
			i++;
		}
		list = list->next;
	}
	if (i == 0)
		del_way(lem);
	fill_way(lem);
}
void	sort_ways(t_lem *lem)
{
	int		x;
	t_pipe	*pipe;
	t_way	*way;
	
	x = 1;
	while (x > 0)
	{
		x = 0;
		if (lem->way->length > lem->way->next->length)
		{
			ft_swap(&lem->way->length, &lem->way->next->length);
			pipe = lem->way->next->pipe;
			lem->way->next->pipe = lem->way->pipe;
			lem->way->pipe = pipe;
			x++;
		}
		way = lem->way;
		while (way->next->next)
		{
			if (way->next->length > way->next->next->length)
			{
				ft_swap(&way->next->length, &way->next->next->length);
				pipe = way->next->next->pipe;
				way->next->next->pipe = way->next->pipe;
				way->next->pipe = pipe;
				x++;
			}
			way = way->next;
		}
	}
}

void	find_all_ways(t_lem *lem)
{
	lem->way = create_way();
	lem->way->pipe = ft_create_pipe(ft_strdup(lem->end->name));
	lem->way->length = 0;
	fill_way(lem);
	if (!lem->way)
	{
		ft_printf("error\n");
		exit (1);
	}
	if (lem->way->next)
		sort_ways(lem);
}