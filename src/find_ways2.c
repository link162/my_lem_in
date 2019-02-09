/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_ways2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:28:36 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 21:28:50 by ybuhai           ###   ########.fr       */
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

void	clone_way_and_add(t_lem *lem, t_way *obj, char *str)
{
	t_way	*start;
	t_pipe	*pipe;

	start = lem->way;
	while (start->next)
		start = start->next;
	start->next = create_way();
	start = start->next;
	start->length = obj->length;
	start->pipe = copy_list_pipes(obj->pipe);
	pipe = start->pipe;
	while (pipe->next->next)
		pipe = pipe->next;
	free(pipe->next->connect);
	pipe->next->connect = str;
	if (!ft_strcmp(str, lem->start->name))
		start->done = 2;
}

int		find_in_list_room_last(t_lem *lem, t_pipe *pipe, char *str)
{
	t_pipe	*tmp;
	t_room	*in;
	t_room	*out;

	tmp = pipe;
	while (pipe->next)
	{
		tmp = pipe;
		if (!ft_strcmp(pipe->connect, str))
			return (1);
		pipe = pipe->next;
	}
	in = find_room(tmp->connect, lem->room);
	out = find_room(str, lem->room);
	if (in->index < out->index)
		return (1);
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
