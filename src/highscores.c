#include "highscores.h"

#define MAX_HIGHSCORES 9

static int highscoreComparator( const void *, const void * );

/*
 *
 */
void
initHighscoreTable( void ) {
  leaderboard.highscore = malloc( sizeof( int32_t ) * MAX_HIGHSCORES );

  for ( int i = 0; i < MAX_HIGHSCORES; i++ ) {
    leaderboard.highscore[i].score  = 0;
    leaderboard.highscore[i].recent = 0;
  }
}

/*
 *
 */
void
addHighscore( int score ) {
  Highscore newHighscores[MAX_HIGHSCORES + 1];

  for ( int i = 0; i < MAX_HIGHSCORES; i++ ) {
    newHighscores[i] = leaderboard.highscore[i];
  }

  newHighscores[MAX_HIGHSCORES].score  = score;
  newHighscores[MAX_HIGHSCORES].recent = 1;

  qsort( newHighscores, MAX_HIGHSCORES + 1, sizeof( Highscore ), highscoreComparator );

  for ( int i = 0; i < MAX_HIGHSCORES; i++ ) {
    leaderboard.highscore[i]        = newHighscores[i];
    leaderboard.highscore[i].recent = 0;
  }
}

/*
 *
 */
void
drawHighscores( void ) {
  int y;

  y = 150;

  drawText( 425, 70, 0xff, 0xff, 0xff, "HIGHSCORES" );

  for ( int i = 0; i < MAX_HIGHSCORES; i++ ) {
    drawText( 425, y, 0xff, 0xff, 0, "#%d ................ %03d", ( i + 1 ),
              leaderboard.highscore[i].score );
    y += 50;
  }

  drawText( 425, 600, 0xff, 0xff, 0xff, "PRESS FIRE TO PLAY!" );
}

void
freeHighscores() {
  free( leaderboard.highscore );
}

static int
highscoreComparator( const void *a, const void *b ) {
  Highscore *h1 = ( ( Highscore * ) a );
  Highscore *h2 = ( ( Highscore * ) b );

  return h2->score - h1->score;
}