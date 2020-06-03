#include "stage.h"

static void tick(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void updatePlayer(void);
static void updateBullets(void);
static void drawPlayer(void);
static void drawBullets(void);

static Entity* player;
static SDL_Texture* bulletTexture;

void initStage(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;

  initPlayer();

  bulletTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/bullet.png");
}

static void initPlayer() {
  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));

  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->x = 100;
  player->y = 100;
  player->texture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/player.png");

  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

static void tick() {
  updatePlayer();
  updateBullets();
}

static void updatePlayer() {
  player->dx = 0;
  player->dy = 0;

  if (player->reload > 0) {
    player->reload--;
  }

  if (app.keyboard[SDL_SCANCODE_UP]) {
    player->dy = -PLAYER_SPEED;
  }
  if (app.keyboard[SDL_SCANCODE_DOWN]) {
    player->dy = PLAYER_SPEED;
  }
  if (app.keyboard[SDL_SCANCODE_LEFT]) {
    player->dx = -PLAYER_SPEED;
  }
  if (app.keyboard[SDL_SCANCODE_RIGHT]) {
    player->dx = PLAYER_SPEED;
  }
  if (app.keyboard[SDL_SCANCODE_LCTRL] && player->reload == 0) {
    fireBullet();
  }

  player->x += player->dx;
  player->y += player->dy;
}

static void fireBullet() {
  Entity* bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));

  stage.bulletTail->next = bullet;
  stage.bulletTail = bullet;

  bullet->x = player->x + 5;
  bullet->y = player->y;
  bullet->dx = PLAYER_SPEED;
  bullet->dy = randomFloat(-3, 3);
  bullet->health = 1;
  bullet->texture = bulletTexture;
  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  bullet->y += (player->h / 2) - (bullet->h / 2);

  player->reload = 8;
}

static void updateBullets() {
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    b->x += b->dx;
    b->y += b->dy;

    if (b->x > SCREEN_WIDTH) {
      if(b == stage.bulletTail) {
        stage.bulletTail = prev;
        prev->next = b->next;
        free(b);
        b = prev;
      }
    }
    prev = b;
  }
}

static void draw() {
  drawPlayer();
  drawBullets();
}

static void drawPlayer() {
  blit(player->texture, player->x, player->y);
}

static void drawBullets() {
  Entity *b;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    blit(b->texture, b->x, b->y);
  }
}
