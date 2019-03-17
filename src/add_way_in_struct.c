/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_way_in_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:54:21 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/17 18:06:16 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		cmp_way_with_group(t_group *group, t_way *way)
{
	t_way *tmp;
	t_way *step;
	t_way *new;

	tmp = group->way;
	while (tmp)
	{
		step = tmp->step;
		while (step->step)
		{
			new = way->step;
			while (new->step)
			{
				if (new->id == step->id)
					return (1);
				new = new->step;
			}
			step = step->step;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		count_steps(t_way *way, int length)
{
	int res;

	res = 0;
	while (way)
	{
		if (way->done == -1)
			break ;
		res += length - way->length;
		way = way->next;
	}
	return (res);
}

void	set_all_index(t_lem *lem, int i)
{
	t_way *way;

	way = lem->group[i].way;
	way->done = 0;
	way = way->next;
	while (way)
	{
		way->done = -1;
		way->done = count_steps(lem->group[i].way, way->length);
		way = way->next;
	}
}

void	count_group_index(t_lem *lem, int i)
{
	int		ant;
	int		count;
	t_way	*way;

	count = 0;
	set_all_index(lem, i);
	ant = lem->ants;
	while (ant)
	{
		way = lem->group[i].way;
		while (way)
		{
			if (ant > way->done)
				ant--;
			way = way->next;
		}
		count++;
	}
	count += lem->group[i].way->length - 1;
	lem->group[i].index = count;
	if (lem->index > count)
		lem->index = count;
}

int		try_add_way_to_group(t_lem *lem, t_way *tmp)
{
	t_way	*way;
	int		i;

	i = -1;
	while (++i < lem->groups)
	{
		if (!cmp_way_with_group(&lem->group[i], tmp))
		{
			way = lem->group[i].way;
			lem->group[i].ways++;
			while (way->next)
				way = way->next;
			way->next = tmp;
			count_group_index(lem, i);
			return (0);
		}
	}
	return (1);
}

void	first_way_in_group(t_lem *lem, int i, t_way *tmp)
{
	lem->groups++;
	lem->group[i].way = tmp;
	lem->group[i].ways = 1;
	lem->group[i].index = tmp->length + lem->ants - 1;
	if (lem->index < 0 || lem->index > lem->group[i].index)
		lem->index = lem->group[i].index;
}

void	add_way_in_struct(t_lem *lem, t_way *tmp)
{
	t_way		*way;
	static int	i;

	tmp->next = NULL;
	if (!i)
	{
		lem->group = (t_group *)malloc(sizeof(t_group) * GROUP);
		first_way_in_group(lem, i++, tmp);
	}
	else if (try_add_way_to_group(lem, tmp))
	{
		if (i < GROUP)
			first_way_in_group(lem, i++, tmp);
		else
			del_way(tmp);
	}
}
