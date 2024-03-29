/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 15:46:24 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/26 13:51:13 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../libft/include/libft.h"
# include "../sdl/SDL2.framework/Versions/A/Headers/SDL.h"
# include "../sdl/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
# include "get_next_line.h"
# include <math.h>
# include <fcntl.h>

////////DEFINITIONS

/*-----RESOLUTION-----*/
# define WIN_W 960
# define WIN_H 640

/*--------FONT--------*/
# define FPS_SIZE 20

/*-------VALUES-------*/
# define TIME_PER_FRAME 16
# define PLAYER_VOL 0.3
# define INF 1000000000

////////STRUCTS

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
	double		m_speed;
	double		r_speed;
	int			is_running;
}				t_player;

/*--------MAP---------*/
typedef struct s_map
{
	char		*file;
	int			**matrix;
	int			width;
	int			height;
}				t_map;

/*--------TEXT--------*/
typedef struct s_text
{
	TTF_Font		*font;
	SDL_Color		color;
	SDL_Surface		*surface;
	char			*str;
}					t_text;

/*--------SDL---------*/
typedef struct s_sdl
{
	SDL_Window			*win;
	SDL_Surface			*screen;
	Uint32				*pixels;
	SDL_Event			event;
	t_text				text;
	SDL_AudioDeviceID	device_id;
	Uint8				*wav_buffer1;
	Uint8				*wav_buffer2;
	Uint8				*wav_buffer3;
}						t_sdl;

/*------TEXTURES------*/
typedef struct textures
{
	SDL_Surface		*wood;
	SDL_Surface		*greystone;
	SDL_Surface		*colorstone;
	SDL_Surface		*bluestone;
	SDL_Surface		*redbrick;
	SDL_Surface		*eagle;
	SDL_Surface		*mossy;
}					t_textures;

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
	double		wall_x;
}				t_ray;

typedef struct floor
{
	t_vector2	ray_dir0;
	t_vector2	ray_dir1;
	t_vector2	step;
	t_vector2	curr;
	t_vector2	cell;
	double		curr_pos;
	double		row_dis;
	int			tex_x;
	int			tex_y;
}				t_floor;

/*--------TEMP-------*/
typedef struct s_temp
{
	double	dir;
	double	plane;
}				t_temp;

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
	t_textures	textures;
	t_map		map;
	int			is_runing;
	int			is_textured;
	int			menu;
	int			fps;
	t_player	player;
	t_frames	frames;
	t_ray		ray;
	t_floor		floor;
	t_temp		temp;
	t_draw		draw;
}				t_core;

////////FUNCTIONS

/*--------MAIN--------*/
void		exit_wolf3d(t_core *core);
void		error_print(t_core *core, char *error_msg);

/*--------INIT--------*/
void		init(t_core *core);
void		init_sdl(t_core *core);
void		init_player(t_core *core);
void		init_textures(t_core *core);

/*------READ MAP------*/
void		read_map(t_core *core);

/*-------RENDER-------*/
void		render_frame(t_core *core);

/*-------MY SDL-------*/
void		set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32		get_pixel(SDL_Surface *surface, int x, int y);
void		clear_window(SDL_Surface *surface);

/*------RAYCASTER-----*/
void		wall_casting(t_core *core);
void		floor_casting(t_core *core);

/*---------DRAW-------*/
void		draw_wall_textured(t_core *core, int x);
void		draw_wall_flat(t_core *core, int x);

/*------CONTROLS------*/
void		controls(t_core *core);

#endif
