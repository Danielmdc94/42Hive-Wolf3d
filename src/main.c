/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:52:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 15:46:54 by dpalacio         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (core->map.matrix)
	{
		while (i < core->map.height)
		{
			if (core->map.matrix[i])
				free(core->map.matrix[i]);
			i++;
		}
		free(core->map.matrix);
	}
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
	core->sdl.rend = SDL_CreateRenderer(core->sdl.win, SDL_RENDERER_SOFTWARE, 0);
	if (!core->sdl.rend)
		error_print(core, "Error: Failed to create renderer");
	SDL_SetRenderDrawColor(core->sdl.rend, 25, 25, 25, 255);
	SDL_RenderClear(core->sdl.rend);
	SDL_RenderPresent(core->sdl.rend);
}

int	main(int argc, char **argv)
{
	t_core	core;
	int		is_runing;

	core.map.matrix = NULL;
	if (argc != 2)
		error_print(&core, "Usage: ./wolf3d <valid_map_path>");
	core.map.file = argv[1];
	ft_putstr("Hello, World!\nYou are visiting ");
	ft_putendl(core.map.file);
	read_map(&core);
	init_sdl(&core);
	//-------------- PRINT MAP
	int x = 0;
	int y = 0;
	while (y < core.map.height)
	{
		while (x < core.map.width)
		{
			printf("%d ", core.map.matrix[y][x]);
			x++;
		}
		printf("\n");
		x = 0;
		y++;
	}
	//-----------------------
	is_runing = 1;
	while (is_runing == 1)
	{
		while (SDL_PollEvent(&core.sdl.event))
		{
			if (core.sdl.event.type == SDL_QUIT)
				is_runing = 0;
		}
	}
	exit_wolf3d(&core);
	return (0);
}
