#include "highscores.h"

static int highscoreComparator(const void*, const void*);
static void tick(void);
static void draw(void);
static void drawHighscores(void);

/*
 *
 */
void initHighscoreTable(void) {
  memset(&leaderboard, 0, sizeof(Leaderboard));

  for (int i = 0; i < MAX_HIGHSCORES; i++) {

    leaderboard.highscore[i].score = MAX_HIGHSCORES - i;
    leaderboard.highscore[i].recent = 0;
  }
}

/*
 *
 */
void initHighscores(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}

/*
 *
 */
void addHighscore(int score) {
  Highscore newHighscores[MAX_HIGHSCORES + 1];

  for (int i = 0; i < MAX_HIGHSCORES; i++) {
    newHighscores[i] = leaderboard.highscore[i];
  }

  newHighscores[MAX_HIGHSCORES].score = score;
  newHighscores[MAX_HIGHSCORES].recent = 1;

  qsort(newHighscores, MAX_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);

  for (int i = 0; i < MAX_HIGHSCORES; i++) {
    leaderboard.highscore[i] = newHighscores[i];
    leaderboard.highscore[i].recent = 0;
  }
}

static int highscoreComparator(const void* a, const void* b) {
  Highscore* h1 = ((Highscore*) a);
  Highscore* h2 = ((Highscore*) b);

  return h2->score - h1->score;
}

/*
 *
 */
static void tick(void) {
  updateBackground();
  updateStarfield();

  if (app.keyboard[SDL_SCANCODE_LCTRL]) {
    initStage();
  }
}

/*
 *
 */
static void draw(void) {
  drawBackground();
  drawStarfield();
  drawHighscores();
}

/*
 *
 */
static void drawHighscores() {
  int y;

  y = 150;

  drawText(425, 70, 0xff, 0xff, 0xff, "HIGHSCORES");

  for (int i = 0; i < MAX_HIGHSCORES; i++) {
    if (leaderboard.highscore[i].recent) {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setup astarted.\n");
      drawText(425, y, 0xff, 0xff, 0, "#%d ................ %03d", (i + 1), leaderboard.highscore[i].score);
    } else {
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Setup bstarted.\n");
      //drawText(425, y, 0xff, 0xff, 0xff, "#%d ................ %03d", (i + 1), leaderboard.highscore[i].score);
    }

    y += 50;
  }

  drawText(425, 600, 0xff, 0xff, 0xff, "PRESS FIRE TO PLAY!");
}
