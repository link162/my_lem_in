/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/06 13:46:25 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/libftprintf.h"

typedef struct		s_group
{
	int				nbr_way;
	struct s_group	*next;
}					t_group;

typedef struct		s_pipe
{
	char			*connect;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_room
{
	int				index;
	int				put;
	int				x;
	int				y;
	char			*name;
	t_pipe			*pipe;
	struct s_room	*next;
}					t_room;

typedef struct		s_way
{
	int				number;
	int				done;
	int				length;
	t_pipe			*pipe;
	struct s_way	*next;
}					t_way;

typedef struct		s_lem
{
	int				ways_in_group;
	int				count_way;
	int				ants;
	t_group			*group;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	t_way			*way;
}					t_lem;

t_room				*ft_create_room(char *data, int x, int y);
t_pipe				*ft_create_pipe(char *data);
t_room				*find_room(char *str, t_room *list);
t_pipe				*copy_list_pipes(t_pipe *old);
void				ft_pipe_push_back(t_pipe **room, char *data);
void				ft_room_push_back(t_lem *lem, char *data, int x, int y);
void				create_tree(t_lem *lem);
void				map_init(t_lem *lem);
char				*dup_room(char *str);
void				check_command(char *line, t_lem *lem);
void				find_index(t_lem *lem);
void				find_all_ways(t_lem *lem);
void				find_uncrossed_ways(t_lem *lem);
int					dup_x(char *line);
int					dup_y(char *line);

#endif
