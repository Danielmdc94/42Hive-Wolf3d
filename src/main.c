/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:52:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/21 16:24:08 by dpalacio         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_core	core;

	core.map.matrix = NULL;
	if (argc != 2)
		error_print(&core, "Usage: ./wolf3d <valid_map_path>");
	core.map.file = argv[1];
	ft_putstr("Hello, World!\nYou are visiting ");
	ft_putendl(core.map.file);
	init(&core);
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
	core.is_runing = 1;
	while (core.is_runing == 1)
	{
		render_frame(&core);
		while (SDL_PollEvent(&core.sdl.event))
		{
			if (core.sdl.event.type == SDL_QUIT)
				core.is_runing = 0;
			if (core.sdl.event.type == SDL_KEYDOWN)
			{
				if (core.sdl.event.key.keysym.sym == SDLK_w)
				{
					core.player.pos.x += core.player.dir.x * core.player.move_speed;
					core.player.pos.y += core.player.dir.y * core.player.move_speed;
				}
				if (core.sdl.event.key.keysym.sym == SDLK_s)
				{
					core.player.pos.x -= core.player.dir.x * core.player.move_speed;
					core.player.pos.y -= core.player.dir.y * core.player.move_speed;
				}
				if (core.sdl.event.key.keysym.sym == SDLK_a)
				{
					double temp_dir = core.player.dir.x;
					core.player.dir.x = core.player.dir.x * cos(-core.player.rot_speed)
						- core.player.dir.y * sin(-core.player.rot_speed);
					core.player.dir.y = temp_dir * sin(-core.player.rot_speed)
						+ core.player.dir.y * cos(-core.player.rot_speed);
					double temp_plane = core.player.plane.x;
					core.player.plane.x = core.player.plane.x * cos(-core.player.rot_speed)
						- core.player.plane.y * sin(-core.player.rot_speed);
					core.player.plane.y = temp_plane * sin(-core.player.rot_speed)
						+ core.player.plane.y * cos(-core.player.rot_speed);
				}
				if (core.sdl.event.key.keysym.sym == SDLK_d)
				{
					double temp_dir = core.player.dir.x;
					core.player.dir.x = core.player.dir.x * cos(core.player.rot_speed)
						- core.player.dir.y * sin(core.player.rot_speed);
					core.player.dir.y = temp_dir * sin(core.player.rot_speed)
						+ core.player.dir.y * cos(core.player.rot_speed);
					double temp_plane = core.player.plane.x;
					core.player.plane.x = core.player.plane.x * cos(core.player.rot_speed)
						- core.player.plane.y * sin(core.player.rot_speed);
					core.player.plane.y = temp_plane * sin(core.player.rot_speed)
						+ core.player.plane.y * cos(core.player.rot_speed);
				}
					
			}
		}
	}
	exit_wolf3d(&core);
	return (0);
}
