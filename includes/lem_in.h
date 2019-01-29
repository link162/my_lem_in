/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybuhai <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:45:34 by ybuhai            #+#    #+#             */
/*   Updated: 2019/01/29 16:58:10 by ybuhai           ###   ########.fr       */
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
	struct s_room	*next;
}					t_room;

#endif
