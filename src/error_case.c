/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_case.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 21:22:47 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/18 16:04:31 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error_case(t_lem *lem)
{
	lem->ants++;
	ft_printf("ERROR\n");
	exit(1);
}

int		cmp_way_with_group(t_group *group, t_way *way)
{
	t_way *tmp;
	t_way *step;
	t_way *new;

	tmp = group->way;
	while (tmp)
	{
		step = tmp->step;
		while (step->step)
		{
			new = way->step;
			while (new->step)
			{
				if (new->id == step->id)
					return (1);
				new = new->step;
			}
			step = step->step;
		}
		tmp = tmp->next;
	}
	return (0);
}

int		count_steps(t_way *way, int length)
{
	int res;

	res = 0;
	while (way)
	{
		if (way->done == -1)
			break ;
		res += length - way->length;
		way = way->next;
	}
	return (res);
}

char	*dup_room(char *str)
{
	int		i;
	char	*res;

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
	while (str[i] == ' ')
		i--;
	res = (char *)malloc(sizeof(char) * (i + 2));
	ft_strncpy(res, str, i + 1);
	res[i + 1] = '\0';
	return (res);
}
