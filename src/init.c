/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:44:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/04 16:57:33 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	init(t_core *core)
{
	read_map(core);
	init_sdl(core);
	init_player(core);
	core->time = 0;
	core->old_time = 0;
}

void	init_sdl(t_core *core)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
		error_print(core, "Error: Failed to initialize SDL2");
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
		error_print(core, "Error: Failed to initialize SDL2_image");
	if(TTF_Init() != 0)
		error_print(core, "Error: Failed to initialize SDL2_ttf");
	core->sdl.win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!core->sdl.win)
		error_print(core, "Error: Failed to create window");
	core->sdl.rend = SDL_CreateRenderer(core->sdl.win,
			SDL_RENDERER_SOFTWARE, 0);
	if (!core->sdl.rend)
		error_print(core, "Error: Failed to create renderer");

	core->sdl.surface = SDL_LoadBMP("textures/bluestone.bmp");
	if (!core->sdl.surface)
		error_print(core, "Error: Failed to load texture");
	//-------------
	core->sdl.texture = SDL_CreateTextureFromSurface(core->sdl.rend, core->sdl.surface);
/*	SDL_Rect	tex;
	SDL_Rect	screen;

	tex.x = 0;
	tex.y = 0;
	tex.w = 1;
	tex.h = core->sdl.surface->h;
	
	screen.x = WIN_W / 4;
	screen.y = WIN_H / 4;
	screen.w = 1;
	screen.h = core->sdl.surface->h * 4;

	SDL_RenderCopy(core->sdl.rend, core->sdl.texture, &tex, &screen);
	SDL_RenderPresent(core->sdl.rend);*/
}

void	init_player(t_core *core)
{
	core->player.pos.x = 2;
	core->player.pos.y = 4;
	core->player.dir.x = 1;
	core->player.dir.y = 0;
	core->player.plane.x = 0;
	core->player.plane.y = 0.66;
}
