#ifndef INIT_H
#define INIT_H

#include "SDL2/SDL_image.h"
#include "commons.h"

extern App app;

extern void initSDL( void );
extern void initAudioContext( void );
extern void cleanup( void );

#endif // INIT_H