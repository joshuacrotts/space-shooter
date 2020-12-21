#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "commons.h"
#include "draw.h"

extern App app;

extern void initBackground( void );
extern void initStarfield( void );
extern void updateBackground( void );
extern void updateStarfield( void );
extern void drawBackground( void );
extern void drawStarfield( void );

#endif // BACKGROUND_H