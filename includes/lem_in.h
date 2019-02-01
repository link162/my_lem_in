/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/01 15:38:25 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/libftprintf.h"

typedef struct		s_pipe
{
	char			*connect;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_room
{
	char			*name;
	t_pipe			*pipe;
	struct s_room	*next;
}					t_room;

typedef struct		s_lem
{
	int				ants;
	t_room			*room;
	t_room			*start;
	t_room			*end;
}					t_lem;

t_room				*ft_create_room(char *data);
t_pipe				*ft_create_pipe(char *data);
void				ft_pipe_push_back(t_room *room, char *data);
void				ft_room_push_back(t_lem *lem, char *data);
void				create_tree(t_lem *lem);
#endif
