/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/11 17:10:26 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	read_data(t_lem *lem, int i)
{
	char	*l;

	while (get_next_line(0, &l) > 0)
	{
		if (l[0] == 'L')
			error_case(lem);
		if (l[0] == '#')
			check_command(l, lem, NULL);
		else if (lem->ants == 0 && i == 0)
		{
			lem->ants = ft_atoi(l);
			i++;
		}
		else if (indicate_room(l, 0, 0))
		{
			if (ft_room_push_back(lem, dup_room(l), dup_x(l), dup_y(l)))
				error_case(lem);
		}
		else if (ft_strchr(l, '-'))
			check_pipe(l, lem);
		else
			error_case(lem);
		free(l);
	}
	create_tree(lem);
}

void	check_errors(t_lem *lem)
{
	t_room *room;

	if (lem->ants < 1)
		error_case(lem);
	if (!lem->start)
		error_case(lem);
	if (!lem->end)
		error_case(lem);
	room = lem->room;
	while (room)
	{
		if (!room->pipe)
			error_case(lem);
		room = room->next;
	}
}

int		main(void)
{
	t_lem	lem;

	map_init(&lem);
	read_data(&lem, 0);
	check_errors(&lem);
	find_index(&lem);
	find_all_ways(&lem);
	print_field(&lem);
	if (lem.count_way > 1)
	{
		find_uncrossed_ways(&lem);
		if (lem.ways_in_group > 1)
		{
			if (is_shortest_way_in_group(&lem))
				choose_group_or_shortway(&lem);
			else
				choose_group(&lem);
		}
		else
			choose_short_way(&lem);
	}
	else
		choose_short_way(&lem);
	clear_data(&lem);
}
