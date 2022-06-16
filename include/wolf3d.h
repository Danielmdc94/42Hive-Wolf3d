/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:46:24 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/16 21:14:03 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define FRACTOL_H

# include "../libft/include/libft.h"
# include "../sdl/include/SDL.h"
# include <math.h>

/*-----RESOLUTION-----*/
# define WIN_W 960
# define WIN_H 640

/*-----2D VECTORS-----*/
typedef struct s_vector2
{
	double		x;
	double		y;
}				t_vector2;

/*-------PLAYER-------*/
typedef struct s_player
{
	t_vector2	pos;
	t_vector2	dir;
}				t_player;

/*--------CORE--------*/
typedef struct s_core
{
	t_player	player;
}				t_core;

#endif
