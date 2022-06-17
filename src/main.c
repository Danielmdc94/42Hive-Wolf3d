/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:52:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 11:41:52 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	error_print(t_core *core, char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit_wolf3d(core);
}

void	exit_wolf3d(t_core *core)
{
	if (core->sdl.win)
		SDL_DestroyWindow(core->sdl.win);
	SDL_Quit();
	exit(0);
}

void	init_sdl(t_core *core)
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0)
		error_print(core, "Error: Failed to initialize SDL2");
	core->sdl.win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!core->sdl.win)
		error_print(core, "Error: Failed to create window");
	core->sdl.rend = SDL_CreateRenderer(core->sdl.win, -1, 0);
	if (!core->sdl.rend)
		error_print(core, "Error: Failed to create renderer");
}

int	main(int argc, char **argv)
{
	t_core	core;
	int		is_runing;
	
	if (argc != 2)
		error_print(&core, "Usage: ./wolf3d <valid_map_path>");
	ft_putstr("Hello, World!\n");
	core.map.file = argv[1];
	//read_map(&core, file)
	init_sdl(&core);
	is_runing = 1;
	SDL_SetRenderDrawColor(core.sdl.rend, 80, 200, 100, 255);
	SDL_RenderClear(core.sdl.rend);
	SDL_RenderPresent(core.sdl.rend);
	while (is_runing == 1)
	{
		while (SDL_PollEvent(&core.sdl.event))
		{
			if (core.sdl.event.type == SDL_QUIT)
				is_runing = 0;
		}
	}
	SDL_DestroyWindow(core.sdl.win);
	SDL_Quit();
	return (0);
}
