/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:44:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 19:26:01 by dpalacio         ###   ########.fr       */
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
	core->sdl.win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!core->sdl.win)
		error_print(core, "Error: Failed to create window");
	core->sdl.rend = SDL_CreateRenderer(core->sdl.win,
			SDL_RENDERER_SOFTWARE, 0);
	if (!core->sdl.rend)
		error_print(core, "Error: Failed to create renderer");
	SDL_SetRenderDrawColor(core->sdl.rend, 25, 25, 25, 255);
	SDL_RenderClear(core->sdl.rend);
	SDL_RenderPresent(core->sdl.rend);
}

void	init_player(t_core *core)
{
	core->player.pos.x = 3;
	core->player.pos.y = 9;
	core->player.dir.x = 1;
	core->player.dir.y = 0;
	core->player.plane.x = 0;
	core->player.plane.y = 0.66;
}
