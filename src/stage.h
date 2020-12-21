#ifndef STAGE_H
#define STAGE_H

#include "background.h"
#include "commons.h"
#include "draw.h"
#include "highscores.h"
#include "sound.h"
#include "text.h"

extern App   app;
extern Stage stage;

extern void         blit( SDL_Texture *texture, int x, int y );
extern SDL_Texture *loadTexture( char *filename );

#endif // STAGE_H