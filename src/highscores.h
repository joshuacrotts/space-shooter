#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include "commons.h"
#include "draw.h"
#include "main.h"
#include "stage.h"
#include "structs.h"
#include "text.h"

extern App  app;
Leaderboard leaderboard;

extern void initHighscoreTable( void );
extern void initHighscores( void );
extern void addHighscore( int score );
extern void drawHighscores( void );

#endif // HIGHSCORES_H