/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:17:39 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/08 19:23:53 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

/*
void	draw_wall_textured(t_core *core, int x)
{
	int			tex_x;
	int			tex_y;
	double		step;
	int			y;
	double		tex_pos;


	tex_x = (int)(core->ray.wall_x * (double)(core->textures.surface->w));
	if (core->ray.face == 0 && core->ray.dir.x > 0)
		tex_x = core->textures.surface->w - tex_x - 1;
	if (core->ray.face == 1 && core->ray.dir.y < 0)
		tex_x = core->textures.surface->w - tex_x - 1;
	step = (core->textures.surface->h) / core->draw.height;
	tex_pos = (core->draw.start - WIN_H / 2 + core->draw.height / 2) * step;
	y = core->draw.start;
	while (y < core->draw.end)
	{
		tex_y = (int)tex_pos & (core->textures.surface->h - 1);
		tex_pos += step;
		x = 0;
		ft_memcpy(core->sdl.screen->pixels + (WIN_H * y + x) * 16,
				core->textures.surface->pixels + (core->textures.surface->h * tex_y + tex_x) * 12,
				sizeof(Uint32));
//		core->sdl.pixels = core->textures.surface->pixels[core->textures.surface->w * tex_y + tex_x];
//		core->sdl.screen->pixels[WIN_W * y + x] = core->sdl.pixels;
		y++;
	}
}
*/
void	draw_wall_textured(t_core *core, int x)
{
	double		wall_x;
	SDL_Rect	wall;
	SDL_Rect	texture;

	wall.x = x;
	wall.y = core->draw.start;
	wall.w = 1;
	wall.h = core->draw.height;
	texture.y = 0;
	texture.w = 1;
	texture.h = core->textures.surface->h;
	if (core->ray.face == 0)
		wall_x = core->player.pos.y + core->ray.perp_wall_dis * core->ray.dir.y;
	else
		wall_x = core->player.pos.x + core->ray.perp_wall_dis * core->ray.dir.x;
	wall_x -= floor(wall_x);
	texture.x = (int)(wall_x * (double)(core->textures.surface->w));
	if (core->ray.face == 0 && core->ray.dir.x > 0)
		texture.x = core->textures.surface->w - texture.x - 1;
	if (core->ray.face == 1 && core->ray.dir.y < 0)
		texture.x = core->textures.surface->w - texture.x - 1;
	set_pixel(core->sdl.screen, x, core->draw.start, 0xFFFFFFFF);
//	if (core->map.matrix[(int)core->ray.map_pos.y]
//		[(int)core->ray.map_pos.x] != 0)
//		SDL_RenderCopy(core->sdl.rend, core->textures.wood, &texture, &wall);
//		SDL_BlitSurface(core->textures.surface, &texture, core->sdl.screen, &wall);
/*	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 2)
		SDL_RenderCopy(core->sdl.rend, core->textures.greystone,
			&texture, &wall);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 3)
		SDL_RenderCopy(core->sdl.rend, core->textures.colorstone,
			&texture, &wall);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 4)
		SDL_RenderCopy(core->sdl.rend, core->textures.bluestone,
			&texture, &wall);
	else
		SDL_RenderCopy(core->sdl.rend, core->textures.redbrick,
			&texture, &wall);*/
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

	target_pixel = (Uint32 *)((Uint8 *)surface->pixels
			+ y * surface->pitch
			+ x * surface->format->BytesPerPixel);
	*target_pixel = pixel;
}
