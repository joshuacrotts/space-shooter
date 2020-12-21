#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL.h"
#define MAX_KEYBOARD_KEYS   350

typedef struct Entity Entity;
typedef struct Explosion Explosion;
typedef struct Debris Debris;
typedef struct FireTrail FireTrail;
typedef struct ExplosionParticle ExplosionParticle;

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

typedef struct Entity {
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
} Entity;

typedef struct Explosion {
  float x;
  float y;
  float dx;
  float dy;
  int r, g, b, a;
  Explosion* next;
} Explosion;

typedef struct FireTrail {
  float x;
  float y;
  float dx;
  float dy;
  float dim;
  SDL_Rect rect;
} FireTrail;

typedef struct ExplosionParticle {
  float x;
  float y;
  float dx;
  float dy;
  float dim;
  float grayscaleColor;
  SDL_Rect rect;
  ExplosionParticle* next;
} ExplosionParticle;

typedef struct Debris {
  float x;
  float y;
  float dx;
  float dy;
  int life;
  SDL_Rect rect;
  SDL_Texture* texture;
  Debris* next;
} Debris;

typedef struct Star {
  int x;
  int y;
  int speed;
} Star;

typedef struct Highscore {
  int score;
  int recent;
} Highscore;

typedef struct Leaderboard {
  Highscore *highscore;
} Leaderboard;

typedef struct Stage {
  int score;
  int gameState;

  Entity fighterHead, *fighterTail;
  Entity bulletHead, *bulletTail;
  Entity pointsHead, *pointsTail;
  Explosion explosionHead, *explosionTail;
  Debris debrisHead, *debrisTail;
  FireTrail fireHead, *fireTail;
  ExplosionParticle explosionParticleHead, *explosionParticleTail;
} Stage;

#endif // STRUCTS_H