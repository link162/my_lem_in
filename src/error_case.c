/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:22:47 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/09 22:35:54 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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

void	error_case(t_lem *lem)
{
	ft_printf("ERROR\n");
	clear_data(lem);
}
