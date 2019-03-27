/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_big.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 13:42:44 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/21 09:27:45 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_way(t_lem *lem, t_way *way)
{
	t_way *tmp;

	if (!lem->way)
		lem->way = way;
	else
	{
		tmp = lem->way;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = way;
	}
}

void	find_best_room(t_lem *lem, int id, t_way *way)
{
	static int	i;
	int			candidat;
	t_pipe		*pipe;

	pipe = lem->room[id].pipe;
	candidat = pipe->id;
	while (pipe)
	{
		if ((lem->room[pipe->id].index < lem->room[candidat].index &&
				lem->room[pipe->id].vizit != 9) || pipe->id == 0 ||
				lem->room[candidat].vizit == 9 || (id == 1 && i == 1))
		{
			if (!(i == 1 && id == 1 && pipe->id == 0))
				candidat = pipe->id;
			if (i == 0 && id == 1 && pipe->id == 0)
				i++;
		}
		pipe = pipe->next;
	}
	way->step = create_way(candidat, 0);
	if (candidat)
	{
		lem->room[candidat].vizit = 9;
		find_best_room(lem, candidat, way->step);
	}
}

t_way	*make_way(t_lem *lem)
{
	t_way *new;

	new = create_way(1, lem->room[1].index);
	find_best_room(lem, 1, new);
	return (new);
}

void	delete_short(t_lem *lem, int *i)
{
	t_pipe *pipe;
	t_pipe *tmp;

	(*i)++;
	if (lem->room[0].pipe->id == 1)
	{
		tmp = lem->room[0].pipe->next;
		free(lem->room[0].pipe->connect);
		free(lem->room[0].pipe);
		lem->room[0].pipe = tmp;
		return ;
	}
	pipe = lem->room[0].pipe;
	while (pipe->next)
	{
		if (pipe->next->id == 1)
		{
			tmp = pipe->next->next;
			free(pipe->next->connect);
			free(pipe->next);
			pipe->next = tmp;
			return ;
		}
		pipe = pipe->next;
	}
}

void	algorithm_big(t_lem *lem)
{
	static int	i;

	while (1)
	{
		if (i == 5)
			delete_short(lem, &i);
		set_index(lem, NULL);
		if (lem->room[1].index == 0)
			break ;
		if (lem->room[1].index == 1)
			i = 5;
		add_way(lem, make_way(lem));
		lem->ways++;
	}
	if (lem->ways == 0)
		error_case(lem);
	lem->group = (t_group *)malloc(sizeof(t_group));
	lem->group->ways = lem->ways;
	lem->group->way = lem->way;
	count_group_index(lem, 0);
}
