/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:46:24 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 11:40:30 by dpalacio         ###   ########.fr       */
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

/*--------MAP---------*/
typedef struct s_map
{
	char		*file;
	int			**matrix;
	int			x;
	int			y;
}				t_map;

/*--------SDL---------*/
typedef struct s_sdl
{
	SDL_Window	*win;
	SDL_Renderer *rend;
	SDL_Event event;
}				t_sdl;

/*--------CORE--------*/
typedef struct s_core
{
	t_sdl		sdl;
	t_map		map;
	t_player	player;
}				t_core;

/*--------MAIN--------*/
void	init_sdl(t_core *core);
void	exit_wolf3d(t_core *core);
void	error_print(t_core *core, char *error_msg);

#endif
