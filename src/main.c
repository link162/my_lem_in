/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/31 18:22:55 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	map_init(t_lem *lem)
{
	lem->ants = 0;
	lem->room = NULL;
	lem->start = NULL;
	lem->end = NULL;
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
	return (res);
}

void	check_command(char *line, t_lem *lem)
{
	char *str;

	if (!ft_strcmp(line, "##start"))
	{
		get_next_line(0, &str);
		lem->start = dup_room(str);
		ft_room_push_back(lem, ft_strdup(lem->start));
		free(str);
	}
	else if (!ft_strcmp(line, "##end"))
	{
		get_next_line(0, &str);
		lem->end = dup_room(str);
		ft_room_push_back(lem, ft_strdup(lem->end));
		free(str);
	}
}

void	check_room(char *line, t_lem *lem)
{
	if (!lem->room)
		lem->room = ft_create_room(dup_room(line));
	else
		ft_room_push_back(lem, dup_room(line));
}

void	add_pipe_to_struct(t_lem *lem, char *from, char *to)
{
	t_room *new;

	new = lem->room;
	while (new)
	{
		if (!ft_strcmp(new->name, from))
		{
			ft_pipe_push_back(new, to);
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

void	read_data(t_lem *lem)
{
	char *line;

	while (get_next_line(0, &line) > 0)
	{
		if (line[0] == '#')
			check_command(line, lem);
		else if (lem->ants == 0)
			lem->ants = ft_atoi(line);
		else if (ft_strchr(line, ' '))
			check_room(line, lem);
		else if (ft_strchr(line, '-'))
			check_pipe(line, lem);
		else
			ft_printf("***%s***\n", line);
		free(line);
	}

}

int main(void)
{
	t_lem	lem;

	map_init(&lem);
	read_data(&lem);

	ft_printf("ants  - %i\n", lem.ants);
	ft_printf("start - %s\n", lem.start);
	ft_printf("end   - %s\n", lem.end);
	t_room *new;
	t_pipe *pipe;
	new = lem.room;
	while (new)
	{
		ft_printf("room name -%s, connect to\n", new->name);
		pipe = new->pipe;
		while (pipe)
		{
			ft_printf("pipe %s\n", pipe->connect);
			pipe = pipe->next;
		}
		new = new->next;
	}
}
