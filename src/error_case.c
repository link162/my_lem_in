/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:22:47 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/02 16:45:33 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del_pipes(t_pipe **pipes)
{
	t_pipe *tmp;
	t_pipe *help;

	tmp = *pipes;
	while (tmp)
	{
		help = tmp->next;
		if (tmp->connect)
			free(tmp->connect);
		free(tmp);
		tmp = help;
	}
	*pipes = NULL;
}

void	free_start_end(t_lem *lem)
{
	if (lem->start)
	{
		if (lem->start->name)
			free(lem->start->name);
		del_pipes(&lem->start->pipe);
		free(lem->start);
	}
	if (lem->end)
	{
		if (lem->end->name)
			free(lem->end->name);
		del_pipes(&lem->end->pipe);
		free(lem->end);
	}

}

void	clear_data(t_lem *lem)
{
	t_room	*room;

	del_pipes(&lem->pipes);
	while (lem->room)
	{
		room = lem->room->next;
		if (lem->room->name)
			free(lem->room->name);
		del_pipes(&lem->room->pipe);
		free(lem->room);
		lem->room = room;
	}
	free_start_end(lem);
	get_next_line(-5, NULL);
}

void	error_case(t_lem *lem)
{
	ft_printf("ERROR\n");
	exit (1);
//	clear_data(lem);
}
