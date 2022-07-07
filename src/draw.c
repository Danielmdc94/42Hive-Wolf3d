/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:17:39 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/07 16:22:09 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

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
	if (core->map.matrix[(int)core->ray.map_pos.y]
		[(int)core->ray.map_pos.x] == 1)
		SDL_RenderCopy(core->sdl.rend, core->textures.wood, &texture, &wall);
	else if (core->map.matrix[(int)core->ray.map_pos.y]
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
			&texture, &wall);
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
