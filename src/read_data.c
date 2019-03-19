/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/19 15:04:41 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		indicate_room(char *str, int i, int x)
{
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

t_room	*ft_create_room(char *data, int x, int y)
{
	t_room	*list;

	list = NULL;
	list = (t_room *)malloc(sizeof(t_room));
	if (list)
	{
		list->name = data;
		list->x = x;
		list->y = y;
		list->next = NULL;
		list->pipe = NULL;
	}
	return (list);
}

int		ft_room_push_back(t_lem *lem, char *data, int x, int y)
{
	t_room	*list;

	list = lem->room;
	if (list)
	{
		if ((list->x == x && list->y == y) || !ft_strcmp(data, list->name))
			return (1);
		while (list->next)
		{
			if ((list->next->x == x && list->next->y == y) ||
							!ft_strcmp(data, list->next->name))
				return (1);
			list = list->next;
		}
		list->next = ft_create_room(data, x, y);
	}
	else
		lem->room = ft_create_room(data, x, y);
	return (0);
}

void	check_command(char *line, t_lem *lem, char *s)
{
	if (!ft_strcmp(line, "##start"))
	{
		while (get_next_line(0, &s) > 0)
		{
			if (indicate_room(s, 0, 0))
			{
				lem->start = ft_create_room(dup_room(s), dup_x(s), dup_y(s));
				ft_room_push_back(lem, dup_room(s), dup_x(s), dup_y(s));
				free(s);
				return ;
			}
			else if (s[0] != '#')
				error_case(lem);
			free(s);
		}
		error_case(lem);
	}
	check_command_end(line, lem, s);
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
			check_ants(lem, l, i++);
		else if (indicate_room(l, 0, 0))
		{
			if (ft_room_push_back(lem, dup_room(l), dup_x(l), dup_y(l)))
				error_case(lem);
		}
		else if (ft_strchr(l, '-'))
			check_pipe(l, lem);
		else
		{
			free(l);
			return ;
		}
		free(l);
	}
}
