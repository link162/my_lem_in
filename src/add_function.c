/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 11:48:17 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/11 15:48:48 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	choose_helper(t_lem *lem, int steps, t_road *road, int a)
{
	t_road *t;

	while (steps)
	{
		t = road;
		while (t->room)
		{
			if (t->room->ant > 0 && ft_strcmp(t->room->name, lem->start->name))
			{
				ft_printf("L%i-%s ", t->room->ant, t->name);
				t->ant = t->room->ant;
				t->room->ant = 0;
			}
			else if (!ft_strcmp(t->room->name, lem->start->name) && a)
			{
				ft_printf("L%i-%s ", lem->ants - a + 1, t->name);
				t->ant = lem->ants - a-- + 1;
			}
			t = t->room;
		}
		steps--;
		ft_putchar('\n');
	}
}

void	free_road(t_road *road)
{
	t_road *tmp;
	t_road *help;
	t_road *del;

	while (road)
	{
		tmp = road->next;
		help = road->room;
		while (help)
		{
			del = help->room;
			free(help);
			help = del;
		}
		free(road);
		road = tmp;
	}
}

void	choose_short_way(t_lem *lem)
{
	int		a;
	int		steps;
	t_road	*road;

	a = lem->ants;
	road = make_road(lem->way->pipe);
	steps = lem->way->length + lem->ants - 1;
	choose_helper(lem, steps, road, a);
	free_road(road);
}

int		indicate_room(char *str)
{
	int i;
	int x;

	i = 0;
	while (str[i])
		i++;
	i--;
	while (str[i] == ' ')
		i--;
	x = i;
	while (ft_isdigit(str[i]))
		i--;
	if (i < 3 || x == i || (str[i] != ' ' && str[i] != '-'))
		return (0);
	if (str[i] == '-')
		i--;
	while (str[i] == ' ')
		i--;
	x = i;
	while (ft_isdigit(str[i]))
		i--;
	if (i < 1 || x == i || (str[i] != ' ' && str[i] != '-'))
		return (0);
	if (str[i] == '-')
		i--;
	if (str[i] == ' ' && i > 0)
		return (1);
	return (0);
}
