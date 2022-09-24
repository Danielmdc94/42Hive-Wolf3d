/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sdl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 14:21:25 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/24 14:28:21 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

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
