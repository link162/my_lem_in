/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:36:30 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/18 16:10:40 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_cycle(t_lem *lem, t_way *way, int *a)
{
	int z;

	z = way->done;
	while (way->step)
	{
		if (way->step->ant > 0)
		{
			ft_printf("L%i-%s ", way->step->ant, lem->room[way->id].name);
			way->ant = way->step->ant;
			way->step->ant = 0;
		}
		else if (way->step->id == 0)
		{
			if (lem->ants - *a + 1 > z && lem->ants >= *a)
			{
				ft_printf("L%i-%s ", *a, lem->room[way->id].name);
				way->ant = (*a)++;
			}
		}
		way = way->step;
	}
}

void	print_field(t_lem *lem)
{
	int		i;
	t_pipe	*pipe;

	i = 1;
	ft_printf("%i\n##start\n%s %i %i\n##end\n%s %i %i\n", lem->ants,
			lem->room[0].name, lem->room[0].x, lem->room[0].y,
			lem->room[1].name, lem->room[1].x, lem->room[1].y);
	while (++i < lem->rooms)
		ft_printf("%s %i %i\n", lem->room[i].name, lem->room[i].x,
				lem->room[i].y);
	pipe = lem->pipes;
	while (pipe)
	{
		ft_printf("%s\n", pipe->connect);
		pipe = pipe->next;
	}
	ft_putchar('\n');
}

void	print_lem(t_lem *lem, t_group *group)
{
	t_way	*way;
	int		a;
	int		z;

	z = group->index;
	print_field(lem);
	a = 1;
	group->way->done = 0;
	while (group->index--)
	{
		way = group->way;
		while (way)
		{
			print_cycle(lem, way, &a);
			way = way->next;
		}
		ft_putchar('\n');
	}
	ft_printf("\nLines: %i\n", z);
}

int		dup_y(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ')
		i--;
	while (ft_isdigit(str[i]))
		i--;
	if (str[i] == '-')
		i--;
	if (str[i] == ' ')
		return (ft_atoi(&str[i]));
	return (0);
}

int		dup_x(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ')
		i--;
	while (ft_isdigit(str[i]))
		i--;
	if (str[i] == '-')
		i--;
	while (str[i] == ' ')
		i--;
	while (ft_isdigit(str[i]))
		i--;
	if (str[i] == '-')
		i--;
	if (str[i] == ' ')
		return (ft_atoi(&str[i]));
	return (0);
}
