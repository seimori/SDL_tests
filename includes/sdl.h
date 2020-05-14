#ifndef SDL_H
 #define SDL_H

 #include <stdlib.h>
 #define SDL_MAIN_HANDLED
 #include <SDL2/SDL.h>
 #include "../libft/includes/libft.h"

 #define SCREEN_W 640
 #define SCREEN_H 480
 #define SCREEN_SCALE 1
 #define SCREEN_NAME "Protoype"


 typedef struct		s_screen
 {
	 unsigned int	w;
	 unsigned int	h;
	 const char		*name;
	 SDL_Window		*window;
	 SDL_Renderer	*renderer;
 }					t_screen;


 typedef struct		s_game
 {
	 SDL_bool		running;
	 struct s_game	*(*init)(struct s_game*);
	 struct s_game	*(*quit)(struct s_game*);
	 t_screen		*screen;
 }					t_game;
#endif