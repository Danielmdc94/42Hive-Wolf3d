/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:56:40 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/22 19:04:18 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	on_keydown(t_core *core);
static void	move(t_core *core);
static void	rotate(t_core *core);

void	controls(t_core *core)
{
	if (core->sdl.event.type == SDL_QUIT)
		core->is_runing = 0;
	if (core->sdl.event.type == SDL_KEYDOWN)
		on_keydown(core);
}

static void	on_keydown(t_core *core)
{
	if (core->sdl.event.key.keysym.sym == SDLK_w
		|| core->sdl.event.key.keysym.sym == SDLK_s)
		move(core);
	if (core->sdl.event.key.keysym.sym == SDLK_a
		|| core->sdl.event.key.keysym.sym == SDLK_d)
		rotate(core);
	if (core->sdl.event.key.keysym.sym == SDLK_ESCAPE)
		core->is_runing = 0;
	if (core->sdl.event.key.keysym.sym == SDLK_t && core->is_textured == 0)
		core->is_textured = 1;
	else if (core->sdl.event.key.keysym.sym == SDLK_t && core->is_textured == 1)
		core->is_textured = 2;
	else if (core->sdl.event.key.keysym.sym == SDLK_t && core->is_textured == 2)
		core->is_textured = 0;
}

static void	move(t_core *core)
{
	if (core->sdl.event.key.keysym.sym == SDLK_w)
	{
		if (core->map.matrix[(int)(core->player.pos.y)]
				[(int)(core->player.pos.x + core->player.dir.x
				* core->player.m_speed)] == 0)
			core->player.pos.x += core->player.dir.x * core->player.m_speed;
		if (core->map.matrix[(int)(core->player.pos.y
				+ core->player.dir.y * core->player.m_speed)]
				[(int)(core->player.pos.x)] == 0)
			core->player.pos.y += core->player.dir.y * core->player.m_speed;
	}
	if (core->sdl.event.key.keysym.sym == SDLK_s)
	{
		if (core->map.matrix[(int)(core->player.pos.y)]
				[(int)(core->player.pos.x - core->player.dir.x
				* core->player.m_speed)] == 0)
			core->player.pos.x -= core->player.dir.x * core->player.m_speed;
		if (core->map.matrix[(int)(core->player.pos.y
				- core->player.dir.y * core->player.m_speed)]
				[(int)(core->player.pos.x)] == 0)
			core->player.pos.y -= core->player.dir.y * core->player.m_speed;
	}
}

static void	rotate(t_core *core)
{
	core->temp.dir = core->player.dir.x;
	core->temp.plane = core->player.plane.x;
	if (core->sdl.event.key.keysym.sym == SDLK_a)
	{
		core->player.dir.x = core->player.dir.x * cos(-core->player.r_speed)
			- core->player.dir.y * sin(-core->player.r_speed);
		core->player.dir.y = core->temp.dir * sin(-core->player.r_speed)
			+ core->player.dir.y * cos(-core->player.r_speed);
		core->player.plane.x = core->player.plane.x * cos(-core->player.r_speed)
			- core->player.plane.y * sin(-core->player.r_speed);
		core->player.plane.y = core->temp.plane * sin(-core->player.r_speed)
			+ core->player.plane.y * cos(-core->player.r_speed);
	}
	if (core->sdl.event.key.keysym.sym == SDLK_d)
	{
		core->player.dir.x = core->player.dir.x * cos(core->player.r_speed)
			- core->player.dir.y * sin(core->player.r_speed);
		core->player.dir.y = core->temp.dir * sin(core->player.r_speed)
			+ core->player.dir.y * cos(core->player.r_speed);
		core->player.plane.x = core->player.plane.x * cos(core->player.r_speed)
			- core->player.plane.y * sin(core->player.r_speed);
		core->player.plane.y = core->temp.plane * sin(core->player.r_speed)
			+ core->player.plane.y * cos(core->player.r_speed);
	}
}
