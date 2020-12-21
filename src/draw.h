#ifndef DRAW_H
#define DRAW_H

#include "commons.h"

extern App app;

extern void prepareScene();
extern void presentScene();

extern void         blitRect( SDL_Texture *, SDL_Rect *, int, int );
extern void         blit( SDL_Texture *, int x, int y );
extern SDL_Texture *loadTexture( char * );

#endif // DRAW_H