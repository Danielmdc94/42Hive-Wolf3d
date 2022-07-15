/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:17:39 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/15 16:24:13 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	draw_wall_textured(t_core *core, int x)
{
	int			tex_x;
	int			tex_y;
	double		step;
	int			y;
	double		tex_pos;

	tex_x = (int)(core->ray.wall_x * (double)(core->textures.wood->w));
	if (core->ray.face == 0 && core->ray.dir.x > 0)
		tex_x = core->textures.wood->w - tex_x - 1;
	if (core->ray.face == 1 && core->ray.dir.y < 0)
		tex_x = core->textures.wood->w - tex_x - 1;
	step = 1.0 * (core->textures.wood->h) / core->draw.height;
	tex_pos = (core->draw.start - WIN_H / 2 + core->draw.height / 2) * step;
	y = core->draw.start;
	while (y++ <= core->draw.end)
	{
		tex_y = (int)tex_pos & (core->textures.wood->h - 1);
		tex_pos += step;
		set_pixel(core->sdl.screen, x, y,
			get_pixel(choose_texture(core), tex_x, tex_y));
	}
	while (y++ <= WIN_H)
		set_pixel(core->sdl.screen, x, y - 1, 0x5a6464);
}

SDL_Surface	*choose_texture(t_core *core)
{
	if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 1)
		return (core->textures.greystone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 2)
		return (core->textures.colorstone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 3)
		return (core->textures.bluestone);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 4)
		return (core->textures.redbrick);
	else
		return (core->textures.wood);
}

void	draw_wall_flat(t_core *core, int x)
{
	if (core->ray.face == 0)
		core->draw.color = 200;
	else
		core->draw.color = 150;
	SDL_SetRenderDrawColor(core->sdl.rend,
		core->draw.color - core->ray.perp_wall_dis * 5,
		core->draw.color - core->ray.perp_wall_dis * 5,
		core->draw.color - core->ray.perp_wall_dis * 5, 255);
	SDL_RenderDrawLine(core->sdl.rend, x, core->draw.start,
		x, core->draw.end);
}

void	set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32	*target_pixel;

	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		target_pixel = (Uint32 *)((Uint8 *)surface->pixels
				+ y * surface->pitch
				+ x * surface->format->BytesPerPixel);
	*target_pixel = pixel;
	}
}

Uint32	get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint32	*target_pixel;

	target_pixel = (Uint32 *)((Uint8 *)surface->pixels
			+ y * surface->pitch
			+ x * surface->format->BytesPerPixel);
	return (*target_pixel);
}
