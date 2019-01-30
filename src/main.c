/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:58:49 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/30 19:03:58 by ybuhai           ###   ########.fr       */
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

void	read_data(t_lem *lem)
{
	char *line;

	if (get_next_line(0, &line) > 0)
}

int main(void)
{
	t_lem	lem;

	read_data(&lem);
}
