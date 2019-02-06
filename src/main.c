/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/06 15:07:22 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_pipe_to_struct(t_lem *lem, char *from, char *to)
{
	t_room *new;

	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, from))
		{
			ft_pipe_push_back(&new->pipe, to);
			return ;
		}
		new = new->next;
	}
	if (!new)
	{
		ft_printf("no this room\n");
		exit(1);
	}
}

void	check_pipe(char *line, t_lem *lem)
{
	int		i;
	char	*from;
	char	*to;

	i = 0;
	while (line[i] && line[i] != '-')
		i++;
	from = (char *)malloc(sizeof(char) * (i + 1));
	ft_bzero(from, i + 1);
	ft_strncpy(from, line, i);
	line = line + i + 1;
	i = 0;
	while (line[i])
		i++;
	to = (char *)malloc(sizeof(char) * (i + 1));
	ft_bzero(to, i + 1);
	ft_strncpy(to, line, i);
	add_pipe_to_struct(lem, from, to);
	add_pipe_to_struct(lem, to, from);
}

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
		{
			ft_printf("error map, line \"%s\"", line);
			exit (1);
		}
		free(line);
	}
	create_tree(lem);

}

void	clear_data(t_lem *lem)
{
	t_pipe *way;
	t_room *tmp;

	while (lem->room)
	{
		while (lem->room->pipe)
		{
			way = lem->room->pipe->next;
			free(lem->room->pipe->connect);
			free(lem->room->pipe);
			lem->room->pipe = way;
		}
		tmp = lem->room->next;
		free(lem->room->name);
		free(lem->room);
		lem->room = tmp;
	}
	free(lem->start->name);
	while (lem->start->pipe)
	{
		way = lem->start->pipe->next;
		free(lem->start->pipe->connect);
		free(lem->start->pipe);
		lem->start->pipe = way;
	}
	free(lem->start);
	free(lem->end->name);
	while (lem->end->pipe)
	{
		way = lem->end->pipe->next;
		free(lem->end->pipe->connect);
		free(lem->end->pipe);
		lem->end->pipe = way;
	}
	free(lem->end);
	get_next_line(-5, NULL);
}

void	del_pipe(t_room *list, char *room, char *name)
{
	t_pipe *pipe;
	t_pipe *tmp;

	while (list)
	{
		if (!ft_strcmp(list->name, room))
		{
			pipe = list->pipe;
			if (!ft_strcmp(pipe->connect, name))
			{
				tmp = pipe->next;
				free(pipe->connect);
				free(pipe);
				list->pipe = tmp;
				return ;
			}
			while (pipe->next)
			{
				if (!ft_strcmp(pipe->next->connect, name))
				{
					tmp = pipe->next->next;
					free(pipe->next->connect);
					free(pipe->next);
					pipe->next = tmp;
					return ;
				}
				pipe = pipe->next;
			}
		}
		list = list->next;
	}
}

int		count_pipes(t_room *room)
{
	int		x;
	t_pipe	*tmp;

	x = 0;
	tmp = room->pipe;
	while (tmp)
	{
		x++;
		tmp = tmp->next;
	}
	return (x);
}
int		check_dead_ends(t_lem *lem)
{
	t_room	*new;
	t_room *tmp;

	new = lem->room;
	if (count_pipes(new) == 1)
	{
		tmp = new->next;
		del_pipe(lem->room, new->pipe->connect, new->name);
		free(new->pipe->connect);
		free(new->pipe);
		free(lem->room);
		lem->room = tmp;
		return (1);
	}
	while (new->next)
	{
		if (count_pipes(new->next) == 1)
		{
			tmp = new->next->next;
			del_pipe(lem->room, new->next->pipe->connect, new->next->name);
			free(new->next->pipe->connect);
			free(new->next->pipe);
			free(new->next);
			new->next = tmp;
			return (1);
		}
		new = new->next;
	}
	return (0);
}

void	check_errors(t_lem *lem)
{
	t_room *room;

	if (lem->ants < 1)
	{
		ft_printf("error number of ints\n");
		exit (1);
	}
	if (!lem->start)
	{
		ft_printf("no room start\n");
		exit(1);
	}
	if (!lem->end)
	{
		ft_printf("no room end\n");
		exit (1);
	}
//	while (check_dead_ends(lem))
//		;
	room = lem->room;
	while (room)
	{
		if (!room->pipe)
		{
			ft_printf("room %s have no connections\n", room->name);
			exit (1);
		}
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
	if (lem.count_way > 1)
		find_uncrossed_ways(&lem);

	ft_printf("ants  - %i\n", lem.ants);
	ft_printf("start - %s\n", lem.start->name);
	ft_printf("end   - %s\n", lem.end->name);
	t_room *new;
	t_pipe *pipe;
	new = lem.room;
	while (new)
	{
		ft_printf("room name -%s, x = %i y = %i connect to\n", new->name, new->x, new->y);
		pipe = new->pipe;
		while (pipe)
		{
			ft_printf("pipe %s\n", pipe->connect);
			pipe = pipe->next;
		}
		ft_printf("index -%i\n", new->index);
		new = new->next;
	}
	t_way *way;
	way = lem.way;
	if (!way)
		ft_printf("no possible weys\n");
	while (way)
	{
		pipe = way->pipe;
		ft_printf("way%i length %i from ", way->number, way->length);
		while (pipe)
		{
			ft_printf("- %s ", pipe->connect);
			pipe = pipe->next;
		}
		ft_printf("\n");
		way = way->next;
	}
	t_group *tmp;
	ft_printf("%i possible ways\n", lem.count_way);
	ft_printf("%i ways in group\n", lem.ways_in_group);
	tmp = lem.group;
	while (tmp)
	{
		ft_printf("way-%i,   ", tmp->nbr_way);
		tmp = tmp->next;
	}
	ft_putchar('\n');
	clear_data(&lem);
}
