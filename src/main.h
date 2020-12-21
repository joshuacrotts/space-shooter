#ifndef MAIN_H
#define MAIN_H

#include "commons.h"
#include "sound.h"

App   app;
Stage stage;

extern void cleanup( void );
extern void initSDL( void );
extern void prepareScene( void );
extern void presentScene( void );
extern void processInput( void );
extern void initStage( void );
extern void initFonts( void );

#endif // MAIN_H