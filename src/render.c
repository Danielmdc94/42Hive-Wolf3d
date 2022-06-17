/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/06/17 19:29:25 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render_frame(t_core *core)
{
	SDL_RenderClear(core->sdl.rend);
	core->frames.old_time = core->frames.time;
	core->frames.time = clock();
	core->frames.frame_time = (core->frames.time - core->frames.old_time) / 1000.0;
	core->frames.fps = 1.0 / core->frames.frame_time;

	printf("%f\n",core->frames.fps);

	SDL_RenderPresent(core->sdl.rend);
}
