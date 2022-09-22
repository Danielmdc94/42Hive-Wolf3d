/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpalacio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:44:10 by dpalacio          #+#    #+#             */
/*   Updated: 2022/09/22 21:38:39 by dpalacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

static void	load_music(t_core *core);

/* Calls all the functions that fill necessary data to
 * start the game loop
 */
void	init(t_core *core)
{
	read_map(core);
	init_sdl(core);
	init_textures(core);
	init_player(core);
	core->is_runing = 1;
	core->is_textured = 2;
	core->fps = 60;
}

void	init_sdl(t_core *core)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
		error_print(core, "Error: Failed to initialize SDL2");
	if (TTF_Init() != 0)
		error_print(core, "Error: Failed to initialize SDL2_ttf");
	core->sdl.text.font = TTF_OpenFont("./fonts/ConnectionBold-ER1g.ttf",
			FPS_SIZE);
	if (core->sdl.text.font == NULL)
		error_print(core, "Error: Failed to load text font");
	load_music(core);
	core->sdl.text.color.r = 255;
	core->sdl.text.color.g = 255;
	core->sdl.text.color.b = 255;
	core->sdl.text.color.a = 255;
	core->sdl.win = SDL_CreateWindow("Wolf3d", 0, 0, WIN_W, WIN_H, 0);
	if (!core->sdl.win)
		error_print(core, "Error: Failed to create window");
	core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
}

static void	load_music(t_core *core)
{
	SDL_AudioSpec	wav_spec;
	Uint32			wav_length;

	SDL_LoadWAV("./sounds/01-P.O.W..wav",
		&wav_spec, &core->sdl.wav_buffer, &wav_length);
	core->sdl.device_id = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
	SDL_QueueAudio(core->sdl.device_id, core->sdl.wav_buffer, wav_length);
	SDL_LoadWAV("./sounds/02-Twelfth_Hour.wav",
		&wav_spec, &core->sdl.wav_buffer, &wav_length);
	SDL_QueueAudio(core->sdl.device_id, core->sdl.wav_buffer, wav_length);
	SDL_LoadWAV("./sounds/03-The_Ultimate_Challenge.wav",
		&wav_spec, &core->sdl.wav_buffer, &wav_length);
	SDL_QueueAudio(core->sdl.device_id, core->sdl.wav_buffer, wav_length);
	SDL_PauseAudioDevice(core->sdl.device_id, 0);
}

void	init_player(t_core *core)
{
	core->player.pos.x = 4.5;
	core->player.pos.y = 2.5;
	core->player.dir.x = 1;
	core->player.dir.y = 0;
	core->player.plane.x = 0;
	core->player.plane.y = 0.66;
}

void	init_textures(t_core *core)
{
	core->textures.wood = SDL_LoadBMP("textures/wood.bmp");
	if (!core->textures.wood)
		error_print(core, "Error: Failed to load texture");
	core->textures.greystone = SDL_LoadBMP("textures/greystone.bmp");
	if (!core->textures.greystone)
		error_print(core, "Error: Failed to load texture");
	core->textures.colorstone = SDL_LoadBMP("textures/colorstone.bmp");
	if (!core->textures.colorstone)
		error_print(core, "Error: Failed to load texture");
	core->textures.bluestone = SDL_LoadBMP("textures/bluestone.bmp");
	if (!core->textures.bluestone)
		error_print(core, "Error: Failed to load texture");
	core->textures.redbrick = SDL_LoadBMP("textures/redbrick.bmp");
	if (!core->textures.redbrick)
		error_print(core, "Error: Failed to load texture");
}
