/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 11:52:59 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/16 20:59:06 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int	main(int argc, char **argv)
{
	int	is_runing;
	SDL_Window *win;
	SDL_Renderer *rend;
	SDL_Event event;

	if (argc && argv)
		ft_putstr("Hello, World!\n");

	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0)
		return (1);
	win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!win)
	{
		SDL_Quit();
		return (1);
	}
	rend = SDL_CreateRenderer(win, -1, 0);
	if (!rend)
	{
		SDL_Quit();
		return (1);
	}
	is_runing = 1;
	SDL_SetRenderDrawColor(rend, 80, 200, 100, 255);
	SDL_RenderClear(rend);
	SDL_RenderPresent(rend);
	while (is_runing == 1)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				is_runing = 0;
		}
	}
	SDL_DestroyWindow(win);
	SDL_Quit();
	return (0);
}
