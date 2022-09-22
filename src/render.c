/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/22 14:42:06 by dpalacio         ###   ########.fr       */
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
	if (core->is_textured == 1)
		floor_casting(core);
	wall_casting(core);
	display_ui(core);
	SDL_UpdateWindowSurface(core->sdl.win);
	end = SDL_GetPerformanceCounter();
	elapsed = (end - start) / (float)SDL_GetPerformanceFrequency();
	core->fps = (int)(1.0f / elapsed);
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

void	display_ui(t_core *core)
{
	SDL_Surface	*fps_surface;
	char		*fps_text;

	fps_text = ft_itoa(core->fps);
	fps_text = ft_strjoin(fps_text, " fps. ");
	fps_surface = TTF_RenderText_Solid(core->sdl.text.font,
			fps_text, core->sdl.text.color);
	SDL_BlitSurface(fps_surface, NULL, core->sdl.screen,
		&core->sdl.screen->clip_rect);
	free(fps_text);
	SDL_FreeSurface(fps_surface);
}
