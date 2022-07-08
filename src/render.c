/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/08 19:42:35 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render_frame(t_core *core)
{
	SDL_SetRenderDrawColor(core->sdl.rend, 25, 25, 25, 255);
	SDL_RenderClear(core->sdl.rend);
	core->frames.old_time = core->frames.time;
	core->frames.time = clock();
	core->frames.frame_time = (core->frames.time - core->frames.old_time)
		/ CLOCKS_PER_SEC;
	core->frames.fps = 1.0 / core->frames.frame_time;
	SDL_Delay(1000 / 60 - core->frames.frame_time / 1000);
	core->player.m_speed = core->frames.frame_time * 30;
	core->player.r_speed = core->frames.frame_time * 18;
//-------
	printf("%f\n", core->frames.fps);
//-------
	raycaster(core);
	SDL_BlitSurface(core->textures.surface, NULL, core->sdl.screen, NULL);
	SDL_UpdateWindowSurface(core->sdl.win);
	render_map(core);
	SDL_RenderPresent(core->sdl.rend);
}

//Testing minimap
void	render_map(t_core *core)
{
	SDL_Rect	minimap;
	SDL_Rect	wall;
	SDL_Rect	player;
	int			x;
	int			y;

	minimap.x = WIN_W - 10 * core->map.width;
	minimap.y = 0;
	minimap.w = 10 * core->map.width - 1;
	minimap.h = 10 * core->map.height - 1;
	wall.w = 10;
	wall.h = 10;
	player.x = minimap.x + (int)(core->player.pos.x * 10) - 2;
	player.y = minimap.y + (int)(core->player.pos.y * 10) - 2;
	player.w = 5;
	player.h = 5;
	x = 0;
	y = 0;
	SDL_SetRenderDrawColor(core->sdl.rend, 100, 100, 100, 150);
	SDL_RenderDrawRect(core->sdl.rend, &minimap);
	while (y < core->map.height)
	{
		while (x < core->map.width)
		{
			if (core->map.matrix[y][x] != 0)
			{
				wall.x = minimap.x + x * 10;
				wall.y = minimap.y + y * 10;
				SDL_RenderDrawRect(core->sdl.rend, &wall);
				SDL_RenderFillRect(core->sdl.rend, &wall);
			}
			x++;
		}
		x = 0;
		y++;
	}
	SDL_SetRenderDrawColor(core->sdl.rend, 250, 250, 0, 150);
	SDL_RenderDrawRect(core->sdl.rend, &player);
	SDL_RenderDrawLine(core->sdl.rend,
		minimap.x + (int)(core->player.pos.x * 10),
		minimap.y + (int)(core->player.pos.y * 10),
		minimap.x + (int)(core->player.pos.x * 10) + core->player.dir.x * 6,
		minimap.y + (int)(core->player.pos.y * 10) + core->player.dir.y * 8);
}
