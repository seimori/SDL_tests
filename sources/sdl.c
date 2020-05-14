#include "../includes/sdl.h"

void			initialize_window(t_screen *screen)
{
	screen->window = SDL_CreateWindow(
		screen->name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screen->w,
		screen->h,
		0
	);
}

void			initialize_renderer(t_screen *screen)
{
	screen->renderer = SDL_CreateRenderer(
		screen->window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
}

t_game			*game_init(t_game *game)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ft_printf("SDL error -> %s\n", SDL_GetError());
		exit(1);
	}
	initialize_window(game->screen);
	initialize_renderer(game->screen);
	game->running = SDL_TRUE;
	return (game);
}

t_game			*game_quit(t_game *game)
{
	SDL_DestroyRenderer(game->screen->renderer);
	SDL_DestroyWindow(game->screen->window);
	game->screen->window = NULL;
	game->screen->renderer = NULL;
	SDL_Quit();
	free(game->screen);
	free(game);
	return (game);
}

t_screen		*initialize_screen(t_screen *screen)
{
	screen = (t_screen*)ft_memalloc(sizeof(t_screen));
	screen->w = SCREEN_SCALE * SCREEN_W;
	screen->h = SCREEN_SCALE * SCREEN_H;
	screen->name = SCREEN_NAME;
	screen->window = NULL;
	screen->renderer = NULL;
	return (screen);
}

t_game			*initialize_game(t_game *game)
{
	game = (t_game*)ft_memalloc(sizeof(t_game));
	game->running = SDL_FALSE;
	game->init = game_init;
	game->quit = game_quit;
	game->screen = initialize_screen(game->screen);
	return (game);
}

int				poll_for_quit(int running)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			running = SDL_FALSE;
	}
	return (running);
}

void			draw(SDL_Renderer *renderer)
{
	SDL_Rect	rect;

	rect.x = 20;
	rect.y = 50;
	rect.w = 200;
	rect.h = 100;
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	// SDL_RenderDrawRect(renderer, &rect);
	SDL_RenderFillRect(renderer, &rect);
	SDL_RenderDrawLine(renderer, 10, 200, 300, 400);
}

int				main(void)
{
	t_game		*game;

	game = NULL;
	game = initialize_game(game);
	game = game->init(game);
	while (game->running)
	{
		game->running = poll_for_quit(game->running);
		SDL_SetRenderDrawColor(game->screen->renderer, 50, 50, 50, 255);
		SDL_RenderClear(game->screen->renderer);
		draw(game->screen->renderer);
		SDL_RenderPresent(game->screen->renderer);
	}
	game = game->quit(game);
	return (0);
}