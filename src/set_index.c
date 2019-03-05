/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_index.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 13:28:05 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/05 15:32:42 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	add_to_queue(t_pipe *queue, int id)
{
	while (queue->next)
		queue = queue->next;
	queue->next = ft_create_pipe(NULL, id);
}

void	set_index(t_lem *lem)
{
	t_pipe	*queue;
	t_pipe	*tmp;

	lem->room[0].vizit = 1;
	queue = ft_create_pipe(NULL, 0);
	while (queue)
	{
		tmp = lem->room[queue->id].pipe;
		while (tmp)
		{
			if (lem->room[tmp->id].index == 0 || lem->room[tmp->id].index > lem->room[queue->id].index + 1)
				lem->room[tmp->id].index = lem->room[queue->id].index + 1;
			if (!lem->room[tmp->id].vizit)
			{
				lem->room[tmp->id].vizit = 1;
				add_to_queue(queue, tmp->id);
			}
			tmp = tmp->next;
		}
		tmp = queue->next;
		free(queue);
		queue = tmp;
	}
	lem->room[0].index = 0;
}
