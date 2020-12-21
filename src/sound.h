#ifndef SOUND_H
#define SOUND_H

#include "commons.h"

#include "SDL2/SDL_mixer.h"

extern void initSounds(void);
extern void loadMusic(char*);
extern void playMusic(int);
extern void playSound(int, int);

#endif // SOUND_H