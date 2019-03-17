/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 17:36:30 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/17 19:10:26 by ybuhai           ###   ########.fr       */
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

void	print_lem(t_lem *lem, t_group *group)
{
	t_way	*way;
	t_way	*tmp;
	int		a;
	int		z;

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

char	*dup_room(char *str)
{
	int		i;
	char	*res;

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
	while (str[i] == ' ')
		i--;
	res = (char *)malloc(sizeof(char) * (i + 2));
	ft_strncpy(res, str, i + 1);
	res[i + 1] = '\0';
	return (res);
}
