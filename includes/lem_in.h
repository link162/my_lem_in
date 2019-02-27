/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/27 17:24:10 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/libftprintf.h"

typedef struct		s_pipe
{
	char			*connect;
	int				id;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_room
{
	int				id;
	int				x;
	int				y;
	char			*name;
	t_pipe			*pipe;
	struct s_room	*next;
}					t_room;

typedef	struct		s_way
{
	int				number;
	int				id;
	int				length;
	struct s_way	step;
	struct s_way	*next;
}					t_way;

typedef struct		s_lem
{
	int				rooms;
	int				ants;
	int				ways;
	t_way			*way;
	t_pipe			*pipes;
	t_room			*room;
	t_room			*start;
	t_room			*end;
}					t_lem;

void				error_case(t_lem *lem);
void				check_pipe(char *line, t_lem *lem);
void				read_data(t_lem *lem, int i);
void				add_pipes_to_rooms(t_lem *lem);
void				convert_to_arr(t_lem *lem);
void				find_ways(t_lem *lem);

#endif
