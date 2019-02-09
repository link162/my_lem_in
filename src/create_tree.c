/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 22:44:17 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_pipe	*copy_list_pipes(t_pipe *old)
{
	t_pipe *new;
	t_pipe *tmp;

	new = (t_pipe *)malloc(sizeof(t_pipe));
	new->connect = ft_strdup(old->connect);
	new->next = NULL;
	tmp = new;
	while (old->next)
	{
		tmp->next = (t_pipe *)malloc(sizeof(t_pipe));
		tmp->next->connect = ft_strdup(old->next->connect);
		tmp->next->next = NULL;
		old = old->next;
		tmp = tmp->next;
	}
	return (new);
}

void	create_tree(t_lem *lem)
{
	t_room	*new;

	if (!lem->start || !lem->end)
		error_case(lem);
	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, lem->start->name))
		{
			lem->start->pipe = copy_list_pipes(new->pipe);
			break ;
		}
		new = new->next;
	}
	new = lem->room;
	while (new)
	{
		if (!strcmp(new->name, lem->end->name))
		{
			lem->end->pipe = copy_list_pipes(new->pipe);
			break ;
		}
		new = new->next;
	}
}

void	map_init(t_lem *lem)
{
	lem->ants = 0;
	lem->ways_in_group = 0;
	lem->count_way = 0;
	lem->pipes = NULL;
	lem->room = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->way = NULL;
	lem->group = NULL;
}

char	*dup_room(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	ft_strncpy(res, str, i);
	res[i] = '\0';
	return (res);
}

void	check_command(char *line, t_lem *lem)
{
	char *str;

	if (!ft_strcmp(line, "##start"))
	{
		get_next_line(0, &str);
		lem->start = ft_create_room(dup_room(str), dup_x(str), dup_y(str));
		ft_room_push_back(lem, dup_room(str), dup_x(str), dup_y(str));
		free(str);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		get_next_line(0, &str);
		lem->end = ft_create_room(dup_room(str), dup_x(str), dup_y(str));
		ft_room_push_back(lem, dup_room(str), dup_x(str), dup_y(str));
		free(str);
	}
}
