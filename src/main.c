/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:52:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/23 11:31:39 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

/* Prints an error message before quiting the program safely
 */
void	error_print(t_core *core, char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit_wolf3d(core);
}

/* Removes all allocated space and closes all SDL tools
 */
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
	SDL_CloseAudioDevice(core->sdl.device_id);
	TTF_Quit();
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
	while (core.is_runing == 1)
	{
		render_frame(&core);
		while (SDL_PollEvent(&core.sdl.event))
			controls(&core);
	}
	exit_wolf3d(&core);
	return (0);
}
