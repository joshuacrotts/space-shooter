#include "stage.h"

static void tick(void);
static void draw(void);
static void initPlayer(void);
static void fireBullet(void);
static void updatePlayer(void);
static void updateBullets(void);
static void updateFighters(void);
static void drawPlayer(void);
static void drawBullets(void);
static void drawFighters(void);
static void spawnEnemies();

static int enemySpawnTimer;

static Entity* player;
static SDL_Texture* bulletTexture;
static SDL_Texture* enemyTexture;
static SDL_Texture* alienBulletTexture;

void initStage(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;

  initPlayer();

  bulletTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/bullet.png");
  enemyTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/enemy.png");

  enemySpawnTimer = 0;
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
  updateFighters();
  updateBullets();
  spawnEnemies();
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

static void updateFighters() {
  Entity* e;
  Entity* prev;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    e->x += e->dx;
    e->y += e->dy;

    if (e != player && e->x < -e->w) {
      if (e == stage.fighterTail) {
        stage.fighterTail = prev;
      }
      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static void draw() {
  drawPlayer();
  drawBullets();
  drawFighters();
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

static void drawFighters() {
  Entity* e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    blit(e->texture, e->x, e->y);
  }
}

static void spawnEnemies() {
  Entity* enemy;

  if (--enemySpawnTimer <= 0) {
    enemy = malloc(sizeof(Entity));
    memset(enemy, 0, sizeof(Entity));
    stage.fighterTail->next = enemy;
    stage.fighterTail = enemy;

    enemy->x = SCREEN_WIDTH;
    enemy->y = randomInt(0, SCREEN_HEIGHT);
    enemy->texture = enemyTexture;
    SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

    enemy->dx = randomInt(-4, -2);
    enemySpawnTimer = randomInt(30, 60);
  }
}
