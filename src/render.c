/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/12 17:21:51 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render_frame(t_core *core)
{
	Uint64	start;
	Uint64	end;
	float	elapsed;

	SDL_FillRect(core->sdl.screen, NULL, 0x000000);
	start = SDL_GetPerformanceCounter();
//	SDL_SetRenderDrawColor(core->sdl.rend, 25, 25, 25, 255);
//	SDL_RenderClear(core->sdl.rend);

	raycaster(core);
	SDL_UpdateWindowSurface(core->sdl.win);
//	render_map(core);
//	SDL_RenderPresent(core->sdl.rend);
	end = SDL_GetPerformanceCounter();
	elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
	core->player.m_speed = elapsed * 40.0;
	core->player.r_speed = elapsed * 24.0;
	core->fps = 1.0f / elapsed;
	SDL_Delay(floor(1000.0f / 60.0f - elapsed * 1000.0f));
//-------
	printf("%f\n", core->fps);
	printf("%f\n", core->player.m_speed);
//-------

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
