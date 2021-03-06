/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/03/20 19:19:55 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/libftprintf.h"
# define GROUP 4

typedef struct		s_pipe
{
	char			*connect;
	int				id;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_room
{
	int				vizit;
	int				x;
	int				y;
	int				index;
	char			*name;
	t_pipe			*pipe;
	struct s_room	*next;
}					t_room;

typedef	struct		s_way
{
	int				done;
	int				id;
	int				ant;
	int				length;
	struct s_way	*step;
	struct s_way	*next;
}					t_way;

typedef struct		s_group
{
	int				index;
	int				ways;
	t_way			*way;
}					t_group;

typedef struct		s_lem
{
	int				lines;
	int				rooms;
	int				ants;
	int				ways;
	int				groups;
	int				index;
	t_way			*way;
	t_pipe			*pipes;
	t_room			*room;
	t_room			*start;
	t_room			*end;
	t_group			*group;
	t_group			*big_group;
}					t_lem;

void				add_way_in_struct(t_lem *lem, t_way *way);
void				error_case(t_lem *lem);
void				check_pipe(char *line, t_lem *lem);
void				read_data(t_lem *lem, int i);
void				add_pipes_to_rooms(t_lem *lem);
void				convert_to_arr(t_lem *lem);
void				find_ways(t_lem *lem);
void				del_way(t_way *way);
void				add_comment(t_pipe **tmp, char *data);
void				clear_index_room(t_lem *lem);
void				count_group_index(t_lem *lem, int i);
void				algorithm_big(t_lem *lem);
void				check_ants(t_lem *lem, char *str, int i);
void				print_lem(t_lem *lem, t_group *group);
int					indicate_room(char *str, int i, int x);
int					check_is_done(t_lem *lem, t_way **t, t_way **q, t_way **p);
int					ft_room_push_back(t_lem *lem, char *data, int x, int y);
int					check_room_in_way(t_lem *l, t_way **q, t_way *w, int i);
t_way				*create_way(int id, int length);
t_room				*ft_create_room(char *data, int x, int y);
t_pipe				*ft_create_pipe(char *data, int id);
void				set_index(t_lem *lem, t_pipe *tmp);
int					cmp_way_with_group(t_group *group, t_way *way);
int					count_steps(t_way *way, int length);
char				*dup_room(char *str);
int					dup_x(char *str);
int					dup_y(char *str);

#endif
