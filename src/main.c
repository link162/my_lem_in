/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 22:45:36 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"


int		dup_y(char *str)
{
	int i = 0;

	while (str[i] && str[i] != ' ')
		i++;
	i++;
	while (str[i] && str[i] != ' ')
		i++;
	return (ft_atoi(&str[i + 1]));
}

int		dup_x(char *str)
{
	int i = 0;

	while (str[i] && str[i] != ' ')
		i++;
	return (ft_atoi(&str[i + 1]));
}

void	read_data(t_lem *lem)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#')
			check_command(line, lem);
		else if (lem->ants == 0 && i == 0)
		{
			lem->ants = ft_atoi(line);
			i++;
		}
		else if (ft_strchr(line, ' '))
			ft_room_push_back(lem, dup_room(line), dup_x(line), dup_y(line));
		else if (ft_strchr(line, '-'))
			check_pipe(line, lem);
		else
			error_case(lem);
		free(line);
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

int main(void)
{
	t_lem	lem;

	map_init(&lem);
	read_data(&lem);
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
