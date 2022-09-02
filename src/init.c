/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:44:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/02 15:49:56 by dpalacio         ###   ########.fr       */
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
	core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
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
	core->textures.wood = SDL_LoadBMP("textures/wood.bmp");
	if (!core->textures.wood)
		error_print(core, "Error: Failed to load texture");
	core->textures.greystone = SDL_LoadBMP("textures/greystone.bmp");
	if (!core->textures.greystone)
		error_print(core, "Error: Failed to load texture");
	core->textures.colorstone = SDL_LoadBMP("textures/colorstone.bmp");
	if (!core->textures.colorstone)
		error_print(core, "Error: Failed to load texture");
	core->textures.bluestone = SDL_LoadBMP("textures/bluestone.bmp");
	if (!core->textures.bluestone)
		error_print(core, "Error: Failed to load texture");
	core->textures.redbrick = SDL_LoadBMP("textures/redbrick.bmp");
	if (!core->textures.redbrick)
		error_print(core, "Error: Failed to load texture");
}
