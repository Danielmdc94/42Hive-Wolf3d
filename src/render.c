/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:37:45 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/24 15:06:20 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	render(t_core *core);
static void	display_ui(t_core *core);
static void	display_menu(t_core *core);
static void	text_line(t_core *core, SDL_Rect *clip, char *text);

void	render_frame(t_core *core)
{
	Uint32	start;
	Uint32	end;
	Uint32	delta;

	clear_window(core->sdl.screen);
	start = SDL_GetTicks();
	render(core);
	end = SDL_GetTicks();
	delta = (end - start);
	if (delta < TIME_PER_FRAME)
	{
		SDL_Delay(TIME_PER_FRAME - delta);
		delta = TIME_PER_FRAME;
	}
	if (delta >= TIME_PER_FRAME)
		core->fps = (int)(1000 / delta);
	core->player.m_speed = delta * 0.012;
	core->player.r_speed = delta * 0.012;
	if (core->player.is_running == 1)
		core->player.m_speed *= 2;
}

static void	render(t_core *core)
{
	if (core->menu == 0)
	{
		if (core->is_textured == 1)
			floor_casting(core);
		wall_casting(core);
	}
	display_ui(core);
	SDL_UpdateWindowSurface(core->sdl.win);
}

static void	display_ui(t_core *core)
{
	SDL_Surface	*fps_surface;
	char		*fps_num;
	char		*fps_text;

	fps_num = ft_itoa(core->fps);
	fps_text = ft_strjoin(fps_num, " fps. ");
	free(fps_num);
	fps_surface = TTF_RenderText_Solid(core->sdl.text.font,
			fps_text, core->sdl.text.color);
	SDL_BlitSurface(fps_surface, NULL, core->sdl.screen,
		&core->sdl.screen->clip_rect);
	free(fps_text);
	SDL_FreeSurface(fps_surface);
	if (core->menu == 1)
		display_menu(core);
}

static void	display_menu(t_core *core)
{
	SDL_Rect	clip;

	clip.x = (WIN_W / 2) - 30;
	clip.y = (WIN_H / 2) - 180;
	clip.w = WIN_W;
	clip.h = WIN_H;
	text_line(core, &clip, "MENU");
	clip.x -= 50;
	clip.y += 30;
	text_line(core, &clip, "Toggle Menu: M");
	text_line(core, &clip, "Cycle Textures: T");
	clip.y += 30;
	text_line(core, &clip, "Move: W,A,S,D");
	text_line(core, &clip, "Run: Left Shift");
	clip.y += 30;
	text_line(core, &clip, "Exit: Esc");
	clip.x = 0;
	clip.y = 0;
	clip.w = WIN_W;
	clip.h = WIN_H;
	SDL_SetClipRect(core->sdl.screen, &clip);
}

static void	text_line(t_core *core, SDL_Rect *clip, char *text)
{
	SDL_Surface	*menu_surface;

	menu_surface = TTF_RenderText_Solid(core->sdl.text.font,
			text, core->sdl.text.color);
	SDL_SetClipRect(core->sdl.screen, clip);
	SDL_BlitSurface(menu_surface, NULL, core->sdl.screen,
		&core->sdl.screen->clip_rect);
	clip->y += 40;
}
