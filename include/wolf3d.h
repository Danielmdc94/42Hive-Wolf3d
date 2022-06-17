/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:46:24 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 22:25:48 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define FRACTOL_H

# include "../libft/include/libft.h"
# include "../sdl/include/SDL.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>
# include <time.h>

/*-----RESOLUTION-----*/
# define WIN_W 640
# define WIN_H 480

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
	t_vector2	plane;
}				t_player;

/*--------MAP---------*/
typedef struct s_map
{
	char		*file;
	int			**matrix;
	int			width;
	int			height;
}				t_map;

/*--------SDL---------*/
typedef struct s_sdl
{
	SDL_Window	*win;
	SDL_Renderer *rend;
	SDL_Event event;
}				t_sdl;

/*-------FRAMES-------*/
typedef struct frames
{
	double		time;
	double		old_time;
	double		frame_time;
	double		fps;
}				t_frames;

/*--------RAY---------*/
typedef struct ray
{
	double		camera_x;
	t_vector2	dir;
	t_vector2	map_pos;
	t_vector2	side_dis;
	t_vector2	delta_dis;
	t_vector2	step;
	double		perp_wall_dis;
	int			hit;
	int			face;
}				t_ray;

/*--------DRAW--------*/
typedef struct draw
{
	int			height;
	int			start;
	int			end;
	int			color;
}				t_draw;

/*--------CORE--------*/
typedef struct s_core
{
	t_sdl		sdl;
	t_map		map;
	int			is_runing;
	double		time;
	double		old_time;
	t_player	player;
	t_frames	frames;
	t_ray		ray;
	t_draw		draw;
}				t_core;

/*--------MAIN--------*/
void	exit_wolf3d(t_core *core);
void	error_print(t_core *core, char *error_msg);

/*--------INIT--------*/
void	init(t_core *core);
void	init_sdl(t_core *core);
void	init_player(t_core *core);

/*------READ MAP------*/
void	read_map(t_core *core);

/*--------RENDER-------*/
void	render_frame(t_core *core);

#endif
