/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:44:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/07/08 20:00:21 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	init(t_core *core)
{
	read_map(core);
	init_sdl(core);
	init_textures(core);
	init_player(core);
	core->is_runing = 1;
	core->is_textured = 1;
	core->time = 0;
	core->old_time = 0;
}

void	init_sdl(t_core *core)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
		error_print(core, "Error: Failed to initialize SDL2");
	if (TTF_Init() != 0)
		error_print(core, "Error: Failed to initialize SDL2_ttf");
	core->sdl.win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!core->sdl.win)
		error_print(core, "Error: Failed to create window");
	core->sdl.rend = SDL_CreateRenderer(core->sdl.win,
			SDL_RENDERER_SOFTWARE, 0);
	core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
	if (!core->sdl.rend)
		error_print(core, "Error: Failed to create renderer");
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

void	init_textures(t_core *core)
{
	core->textures.surface = SDL_LoadBMP("textures/wood.bmp");
	if (!core->textures.surface)
		error_print(core, "Error: Failed to load texture");
	core->textures.wood = SDL_CreateTextureFromSurface(core->sdl.rend,
			core->textures.surface);
	core->textures.surface = SDL_LoadBMP("textures/greystone.bmp");
	if (!core->textures.surface)
		error_print(core, "Error: Failed to load texture");
	core->textures.greystone = SDL_CreateTextureFromSurface(core->sdl.rend,
			core->textures.surface);
	core->textures.surface = SDL_LoadBMP("textures/colorstone.bmp");
	if (!core->textures.surface)
		error_print(core, "Error: Failed to load texture");
	core->textures.colorstone = SDL_CreateTextureFromSurface(core->sdl.rend,
			core->textures.surface);
	core->textures.surface = SDL_LoadBMP("textures/bluestone.bmp");
	if (!core->textures.surface)
		error_print(core, "Error: Failed to load texture");
	core->textures.bluestone = SDL_CreateTextureFromSurface(core->sdl.rend,
			core->textures.surface);
	core->textures.surface = SDL_LoadBMP("textures/redbrick.bmp");
	if (!core->textures.surface)
		error_print(core, "Error: Failed to load texture");
	core->textures.redbrick = SDL_CreateTextureFromSurface(core->sdl.rend,
			core->textures.surface);
	SDL_ConvertSurface(core->textures.surface, core->sdl.screen->format, 0);
}
