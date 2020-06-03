#include "SDL2/SDL.h"
#define MAX_KEYBOARD_KEYS   350

typedef struct Entity Entity;

typedef struct Delegate {
  void (*tick)(void);
  void (*draw)(void);
} Delegate;

typedef struct App{
  SDL_Renderer *renderer;
  SDL_Window *window;

  Delegate delegate;
  int keyboard[MAX_KEYBOARD_KEYS];

} App;

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float dx;
	float dy;
	int health;
	int reload;
  int side;
	SDL_Texture *texture;
	Entity *next;
};

typedef struct Stage {
  Entity fighterHead, *fighterTail;
  Entity bulletHead, *bulletTail;
} Stage;
