/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uncrossed_ways.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 11:59:56 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/10 10:20:53 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		try_find_room_in_way(t_pipe *pipe, char *name)
{
	while (pipe)
	{
		if (!ft_strcmp(pipe->connect, name))
			return (1);
		pipe = pipe->next;
	}
	return (0);
}

int		ways_cmp(t_lem *lem, t_way *candidat)
{
	t_group *group;
	t_way	*current;
	t_pipe	*pipe;

	group = lem->group;
	while (group)
	{
		current = find_nbr_way(lem->way, group->nbr_way);
		pipe = current->pipe;
		pipe = pipe->next;
		while (pipe->next)
		{
			if (try_find_room_in_way(candidat->pipe, pipe->connect))
				return (1);
			pipe = pipe->next;
		}
		group = group->next;
	}
	return (0);
}

void	add_last_way(t_group *group, int number)
{
	while (group->next)
		group = group->next;
	group->next = (t_group *)malloc(sizeof(t_group));
	group->next->next = NULL;
	group->next->nbr_way = number;
}

int		start_way(t_lem *lem, int i)
{
	t_way	*nextway;
	int		flag;

	flag = 0;
	lem->group = (t_group *)malloc(sizeof(t_group));
	lem->group->next = NULL;
	lem->group->nbr_way = i;
	while (i < lem->count_way - 1)
	{
		nextway = find_nbr_way(lem->way, i + 1);
		if (!ways_cmp(lem, nextway))
		{
			flag++;
			add_last_way(lem->group, nextway->number);
		}
		i++;
	}
	if (flag == 0)
		free(lem->group);
	return (flag);
}

void	find_uncrossed_ways(t_lem *lem)
{
	int i;
	int res;

	i = 0;
	while (i < lem->count_way)
	{
		res = start_way(lem, i);
		if (res)
		{
			lem->ways_in_group = res + 1;
			break ;
		}
		i++;
	}
	if (res == 0)
		ft_printf("no uncrosses way\n");
}
