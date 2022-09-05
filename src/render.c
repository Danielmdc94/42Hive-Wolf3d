/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/05 13:36:01 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	render_frame(t_core *core)
{
	Uint64	start;
	Uint64	end;
	float	elapsed;

	clear_window(core->sdl.screen);
	start = SDL_GetPerformanceCounter();
	raycaster(core);
	SDL_Color	color = { 255, 255, 255, 255 };
	SDL_Surface	*surface = TTF_RenderText_Solid(core->sdl.font, "Welcome to WOLF3D", color);
		SDL_BlitSurface(surface, NULL, core->sdl.screen, &surface->clip_rect);
	SDL_UpdateWindowSurface(core->sdl.win);
	end = SDL_GetPerformanceCounter();
	elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
	core->player.m_speed = elapsed * 40.0;
	core->player.r_speed = elapsed * 24.0;
	core->fps = 1.0f / elapsed;
//	SDL_Delay(floor(1000.0f / 60.0f - elapsed * 1000.0f));
//-------
	printf("%f\n", core->fps);
//	printf("%f\n", core->player.m_speed);
//	printf("%f\n", core->ray.perp_wall_dis);
//-------
}

void	set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32	*target_pixel;

	if (x < WIN_W && y < WIN_H && x >= 0 && y >= 0)
	{
		target_pixel = (Uint32 *)((Uint8 *)surface->pixels
				+ y * surface->pitch
				+ x * surface->format->BytesPerPixel);
	*target_pixel = pixel;
	}
}

Uint32	get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint32	*target_pixel;

	target_pixel = (Uint32 *)((Uint8 *)surface->pixels
			+ y * surface->pitch
			+ x * surface->format->BytesPerPixel);
	return (*target_pixel);
}

void	clear_window(SDL_Surface *surface)
{
	size_t	len;

	len = surface->w * surface->h * surface->format->BytesPerPixel;
	ft_memset(surface->pixels, 0, len);
}
