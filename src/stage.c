#include "stage.h"

static void tick(void);
static void draw(void);
static void initPlayer(void);
static void initStarfield(void);
static void fireBullet(void);
static void updatePlayer(void);
static void updateBullets(void);
static void updateFighters(void);
static void updateEnemies(void);
static void updateBackground(void);
static void updateExplosions(void);
static void updateDebris(void);
static void updateStarfield(void);
static void drawPlayer(void);
static void drawBullets(void);
static void drawFighters(void);
static void drawBackground(void);
static void drawStarfield(void);
static void drawExplosions(void);
static void drawDebris(void);
static void spawnEnemies(void);
static bool bulletHitFighter(Entity*);
static void fireAlienBullet(Entity*);
static void addExplosion(int, int, int);
static void addDebris(Entity*);
static void clipPlayer(void);
static void resetStage(void);

static int enemySpawnTimer;
static int stageResetTimer;
static int backgroundX;

static Star stars[MAX_STARS];
static Entity* player;
static SDL_Texture* bulletTexture;
static SDL_Texture* enemyTexture;
static SDL_Texture* alienBulletTexture;
static SDL_Texture* playerTexture;
static SDL_Texture* explosionTexture;
static SDL_Texture* background;

/*
 *
 */
void initStage(void) {
  app.delegate.tick = tick;
  app.delegate.draw = draw;

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;
  stage.explosionTail = &stage.explosionHead;
  stage.debrisTail = &stage.debrisHead;
  stage.fireTail = &stage.fireHead;

  playerTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/player.png");
  bulletTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/bullet.png");
  enemyTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/enemy.png");
  alienBulletTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/alienBullet.png");
  explosionTexture = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/explosion.png");
  background = loadTexture("C:/Users/joshu/Desktop/Files/C/SDL_Game_01/gfx/background.png");

  resetStage();
}

/*
 *
 */
static void initPlayer() {
  player = malloc(sizeof(Entity));
  memset(player, 0, sizeof(Entity));

  stage.fighterTail->next = player;
  stage.fighterTail = player;

  player->x = 100;
  player->y = 100;
  player->side = SIDE_PLAYER;
  player->health = 1;
  player->texture = playerTexture;

  SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

/*
 *
 */
static void initStarfield() {
  for(int i = 0; i < MAX_STARS; i++) {
    stars[i].x = randomInt(0, SCREEN_WIDTH);
    stars[i].y = randomInt(0, SCREEN_HEIGHT);
    stars[i].speed = randomInt(1, 8);
  }
}

/*
 *
 */
static void tick() {
  updateBackground();
  updateStarfield();
  updatePlayer();
  updateEnemies();
  updateFighters();
  updateBullets();
  spawnEnemies();
  updateExplosions();
  updateDebris();
  clipPlayer();
  //SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%p.\n", player);
  if (player == NULL && --stageResetTimer <= 0) {
    resetStage();
  }
}

/*
 *
 */
static void updatePlayer() {
  if (player != NULL) {
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
}

/*
 *
 */
static void updateBullets() {
  Entity *b, *prev;

  prev = &stage.bulletHead;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    b->x += b->dx;
    b->y += b->dy;

    if (bulletHitFighter(b) || b->x < -b->w || b->y < -b->h || b->x > SCREEN_WIDTH || b->y > SCREEN_HEIGHT) {
      if(b == stage.bulletTail) {
        stage.bulletTail = prev;
      }
      prev->next = b->next;
      free(b);
      b = prev;
    }
    prev = b;
  }
}

/*
 *
 */
static void updateEnemies() {
  Entity *e;

	for (e = stage.fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e != player && player != NULL && --e->reload <= 0)
		{
			fireAlienBullet(e);
		}
	}
}

/*
 *
 */
static void updateFighters()
{
	Entity* e;
  Entity* prev;

	prev = &stage.fighterHead;

	for (e = stage.fighterHead.next; e != NULL; e = e->next){
		e->x += e->dx;
		e->y += e->dy;

		if (e != player && e->x < -e->w) {
			e->health = 0;
		}

		if (e->health == 0) {
			if (e == player) {
				player = NULL;
			}

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

/*
 *
 */
static void updateBackground() {
  if (--backgroundX < -SCREEN_WIDTH) {
    backgroundX = 0;
  }
}

/*
 *
 */
static void updateStarfield() {
  for (int i = 0; i < MAX_STARS; i++) {
    stars[i].x -= stars[i].speed;

    if (stars[i].x < 0) {
      stars[i].x = SCREEN_WIDTH + stars[i].x;
    }
  }
}

/*
 *
 */
static void updateExplosions() {
  Explosion* e;
  Explosion* prev;

  prev = &stage.explosionHead;

  for(e = stage.explosionHead.next; e != NULL; e = e->next) {
    e->x += e->dx;
    e->y += e->dy;

    if (--e->a <= 0) {
      if (e == stage.explosionTail) {
        stage.explosionTail = prev;
      }
      prev->next = e->next;
      free(e);
      e = prev;
    }
    prev = e;
  }
}

static void updateDebris() {
  Debris* d;
  Debris* prev;

  prev = &stage.debrisHead;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    d->x += d->dx;
    d->y += d->dy;

    d->dy += 0.5;

    if (--d->life <= 0) {
      if (d == stage.debrisTail) {
        stage.debrisTail = prev;
      }

      prev->next = d->next;
      free(d);
      d = prev;
    }
    prev = d;
  }
}

/*
 *
 */
static void draw() {
  drawBackground();

	drawStarfield();

	drawFighters();

	drawDebris();

	drawExplosions();

	drawBullets();
}

/*
 *
 */
static void drawPlayer() {
  blit(player->texture, player->x, player->y);
}

/*
 *
 */
static void drawBullets() {
  Entity *b;

  for (b = stage.bulletHead.next; b != NULL; b = b->next) {
    blit(b->texture, b->x, b->y);
  }
}

/*
 *
 */
static void drawFighters() {
  Entity* e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    blit(e->texture, e->x, e->y);
  }
}

/*
 *
 */
static void drawBackground() {
  SDL_Rect dest;

  for (int x = backgroundX; x < SCREEN_WIDTH; x += SCREEN_WIDTH) {
    dest.x = x;
    dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;

    SDL_RenderCopy(app.renderer, background, NULL, &dest);
  }
}

/*
 *
 */
static void drawStarfield() {
  for (int i = 0; i < MAX_STARS; i++) {
    int c = 32 * stars[i].speed;

    SDL_SetRenderDrawColor(app.renderer, c, c, c, 255);
    SDL_RenderDrawLine(app.renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
  }
}

/*
 *
 */
static void drawDebris() {
  Debris *d;

  for (d = stage.debrisHead.next; d != NULL; d = d->next) {
    blitRect(d->texture, &d->rect, d->x, d->y);
  }
}

/*
 *
 */
static void drawExplosions() {
  Explosion* e;

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(explosionTexture, SDL_BLENDMODE_ADD);

  for (e = stage.explosionHead.next; e != NULL; e = e->next) {
    SDL_SetTextureColorMod(explosionTexture, e->r, e->g, e->b);
    SDL_SetTextureAlphaMod(explosionTexture, e->a);

    blit(explosionTexture, e->x, e->y);
  }

  SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
}

/*
 *
 */
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
    enemy->side = SIDE_ALIEN;
    enemy->health = 1;
    enemy->reload = FRAMES_PER_SECOND * randomInt(1, 3);
    SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);

    enemy->dx = randomInt(-4, -2);
    enemySpawnTimer = randomInt(30, 60);
  }
}

/*
 *
 */
static bool bulletHitFighter(Entity* b) {
  Entity* e;

  for (e = stage.fighterHead.next; e != NULL; e = e->next) {
    if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h)) {
      b->health = 0;
      e->health = 0;
      addExplosion(e->x, e->y, 32);

      addDebris(e);
      return true;
    }
  }

  return false;
}

/*
 *
 */
static void fireBullet() {
  Entity* bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));

  stage.bulletTail->next = bullet;
  stage.bulletTail = bullet;

  bullet->x = player->x + 5;
  bullet->y = player->y;
  bullet->dx = PLAYER_BULLET_SPEED;
  bullet->dy = 0;
  bullet->health = 1;
  bullet->texture = bulletTexture;
  bullet->side = SIDE_PLAYER;

  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  bullet->y += (player->h / 2) - (bullet->h / 2);

  player->reload = 8;
}

/*
 *
 */
static void fireAlienBullet(Entity* e) {
  Entity* bullet;

  bullet = malloc(sizeof(Entity));
  memset(bullet, 0, sizeof(Entity));
  stage.bulletTail->next = bullet;
  stage.bulletTail = bullet;

  bullet->x = e->x;
  bullet->y = e->y;
  bullet->health = 1;
  bullet->texture = alienBulletTexture;
  bullet->side = e->side;
  SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h);

  bullet->x += (e->w / 2) - (bullet->w / 2);
  bullet->y += (e->h / 2) - (bullet->h / 2);

  calcSlope(player->x + (player->w / 2), player->y + (player->h / 2), e->x, e->y, &bullet->dx, &bullet->dy);

  bullet->dx *= ALIEN_BULLET_SPEED;
  bullet->dy *= ALIEN_BULLET_SPEED;

  bullet->side = SIDE_ALIEN;

  e->reload = randomInt(0, FRAMES_PER_SECOND * 2);
}

/*
 *
 */
static void addExplosion(int x, int y, int num) {
  Explosion* e;

  for (int i = 0; i < num; i++) {
    e = malloc(sizeof(Explosion));
    memset(e, 0, sizeof(Explosion));

    stage.explosionTail->next = e;
    stage.explosionTail = e;
    e->x = x + randomFloat(0, 32) - randomFloat(0, 32);
    e->y = y + randomFloat(0, 32) - randomFloat(0, 32);
    e->dx = randomFloat(0, 10) - randomFloat(0, 10);
    e->dy = randomFloat(0, 10) - randomFloat(0, 10);

    e->dx /= 10;
    e->dy /= 10;

    int colorValues = randomInt(0, 3);

    switch(colorValues) {
      case 0:
        e->r = 0xFF;
        break;
      case 1:
        e->r = 0xff;
        e->g = 0x80;
        break;
      case 2:
        e->r = 0xff;
        e->g = 0xff;
      default:
        e->r = 0xff;
        e->g = 0xff;
        e->b = 0xff;
    }

    e->a = randomInt(0, FRAMES_PER_SECOND * 3);
  }
}

/*
 *
 */
static void addDebris(Entity* e) {
  Debris* d;
  int x, y, w, h;

  w = e->w / 2;
  h = e->h / 2;

  for (y = 0; y <= h; y += h) {
    for (x = 0; x <= w; x += w) {
      d = malloc(sizeof(Debris));
      memset(d, 0, sizeof(Debris));
      stage.debrisTail->next = d;
      stage.debrisTail = d;

      d->x = e->x + e->w / 2;
      d->y = e->y + e->h / 2;
      d->dx = randomFloat(0, 5) - randomFloat(0, 5);
      d->dy = randomFloat(-16, -5);
      d->life = FRAMES_PER_SECOND * 2;
      d->texture = e->texture;

      d->rect.x = x;
      d->rect.y = y;
      d->rect.w = w;
      d->rect.h = h;
    }
  }
}

/*
 *
 */
static void addFireParticle(Entity* p) {
  FireTrail* trail;

  trail = malloc(sizeof(FireTrail));
  stage.fireTail.next = trail;
  stage.fireTail = tail;

  trail->x = p->x - p->w / 2;
  trail->y = p->y + p->y / 2;
  trail->dx = randomFloat(-7, -2);
  trail->dy = randomFloat(-3, 3);
  trail->life = FRAMES_PER_SECOND * 6;

  trail->rect.x = x;
  trail->rect.y = y;
  trail->rect.w = randomInt(1, 6);
  trail->rect.h = trail->rect.w;
}

/*
 *
 */
static void resetStage(void) {
  Entity* e;
  Explosion* ex;
  Debris* d;

  while (stage.explosionHead.next) {
    ex = stage.explosionHead.next;
    stage.explosionHead.next = ex->next;
    free(ex);
  }

  while (stage.debrisHead.next) {
    d = stage.debrisHead.next;
    stage.debrisHead.next = ex->next;
    free(d);
  }

  while (stage.fighterHead.next) {
    e = stage.fighterHead.next;
    stage.fighterHead.next = e->next;
    free(e);
  }

  while (stage.bulletHead.next) {
    e = stage.bulletHead.next;
    stage.bulletHead.next = e->next;
    free(e);
  }

  memset(&stage, 0, sizeof(Stage));
  stage.fighterTail = &stage.fighterHead;
  stage.bulletTail = &stage.bulletHead;
  stage.explosionTail = &stage.explosionHead;
  stage.debrisTail = &stage.debrisHead;

  initPlayer();
  initStarfield();

  enemySpawnTimer = 0;

  stageResetTimer = FRAMES_PER_SECOND * 3;
}

/*
 *
 */
static void clipPlayer() {
  if (player != NULL)
  {
    if (player->x < 0)
    {
      player->x = 0;
    }

    if (player->y < 0)
    {
      player->y = 0;
    }

    if (player->x > SCREEN_WIDTH / 2)
    {
      player->x = SCREEN_WIDTH / 2;
    }

    if (player->y > SCREEN_HEIGHT - player->h)
    {
      player->y = SCREEN_HEIGHT - player->h;
    }
  }
}
