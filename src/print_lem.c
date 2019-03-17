/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:36:30 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/17 17:53:44 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_lem(t_lem *lem, t_group *group)
{
	t_way *way;
	t_way *tmp;
	int a;
	int i;
	int z;
	int count;

	count = -1;
	i = 1;
	a = 1;
	group->way->done = 0;
	ft_printf("choose group with index %i, ways in group %i\n", group->index, group->ways);
	while (i)
	{
		count++;
		i = 0;
		way = group->way;
		while (way)
		{
			z = way->done;
			tmp = way;
			while (tmp->step)
			{
				if (tmp->step->ant > 0)
				{
					ft_printf("L%i-%s ", tmp->step->ant, lem->room[tmp->id].name);
					tmp->ant = tmp->step->ant;
					tmp->step->ant = 0;
					i++;
				}
				else if (tmp->step->id == 0)
				{
					if (lem->ants - a + 1 > z && lem->ants >= a)
					{
						i++;
						ft_printf("L%i-%s ", a, lem->room[tmp->id].name);
						tmp->ant = a++;
					}
				}
				tmp = tmp->step;
			}
			way = way->next;
		}
		ft_putchar('\n');
	}
	ft_printf("count %i\n", count);
}
