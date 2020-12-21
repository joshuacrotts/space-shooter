#include "background.h"

static int          backgroundX;
static Star         stars[MAX_STARS];
static SDL_Texture *background;

/*
 *
 */
void
initBackground( void ) {
  background = loadTexture( "gfx/background.png" );
  SDL_LogInfo( SDL_LOG_CATEGORY_APPLICATION, "Background loaded.\n" );
  backgroundX = 0;
}

/*
 *
 */
void
initStarfield() {
  for ( int i = 0; i < MAX_STARS; i++ ) {
    stars[i].x     = randomInt( 0, SCREEN_WIDTH );
    stars[i].y     = randomInt( 0, SCREEN_HEIGHT );
    stars[i].speed = randomInt( 1, 8 );
  }
}

/*
 *
 */
void
updateBackground() {
  if ( --backgroundX < -SCREEN_WIDTH ) {
    backgroundX = 0;
  }
}

/*
 *
 */
void
updateStarfield() {
  for ( int i = 0; i < MAX_STARS; i++ ) {
    stars[i].x -= stars[i].speed;

    if ( stars[i].x < 0 ) {
      stars[i].x = SCREEN_WIDTH + stars[i].x;
    }
  }
}

/*
 *
 */
void
drawBackground() {
  SDL_Rect dest;

  for ( int x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH ) {
    dest.x = x;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy( app.renderer, background, NULL, &dest );
  }
}

/*
 *
 */
void
drawStarfield() {
  for ( int i = 0; i < MAX_STARS; i++ ) {
    int c = 32 * stars[i].speed;

    SDL_SetRenderDrawColor( app.renderer, c, c, c, 255 );
    SDL_RenderDrawLine( app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y );
  }
}
