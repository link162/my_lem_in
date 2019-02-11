/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/02/11 14:42:31 by ybuhai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libftprintf/libftprintf.h"

typedef struct		s_road
{
	int				index;
	int				length;
	int				ant;
	char			*name;
	struct s_road	*room;
	struct s_road	*next;
}					t_road;

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
	t_pipe			*pipes;
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
t_pipe				*find_last_room_in_way(t_pipe *pipe);
t_way				*create_way(void);
t_way				*find_nbr_way(t_way *way, int nbrway);
void				choose_helper(t_lem *lem, int steps, t_road *road, int a);
void				choose_short_way(t_lem *lem);
int					indicate_room(char *str);
void				index_helper(t_lem *c, t_pipe *w, t_room *l, t_room *t);
int					ft_pipe_push_back(t_pipe **room, char *data);
int					find_in_list_room(t_lem *l, t_pipe *p, char *s, int i);
int					ft_room_push_back(t_lem *lem, char *data, int x, int y);
void				error_case(t_lem *lem);
void				clone_way_and_add(t_lem *lem, t_way *obj, char *str);
void				print_field(t_lem *lem);
int					set_numbers(t_way *way);
void				del_pipes(t_pipe **pipes);
void				check_pipe(char *line, t_lem *lem);
t_way				*find_way(t_way *way);
t_road				*make_group_road(t_lem *lem);
void				create_tree(t_lem *lem);
void				map_init(t_lem *lem);
void				check_command(char *line, t_lem *lem);
void				find_index(t_lem *lem);
void				find_all_ways(t_lem *lem);
void				find_uncrossed_ways(t_lem *lem);
void				choose_group_or_shortway(t_lem *lem);
void				choose_group(t_lem *lem);
int					count_way_length(t_lem *lem);
t_road				*make_road(t_pipe *pipe);
void				choose_short_way(t_lem *lem);
void				clear_data(t_lem *lem);
char				*dup_room(char *str);
int					is_shortest_way_in_group(t_lem *lem);
int					dup_x(char *line);
int					dup_y(char *line);
void				free_road(t_road *road);
int					find_in_list_room_last(t_lem *l, t_pipe *p, char *s);

#endif
