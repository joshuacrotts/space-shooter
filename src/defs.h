#define SCREEN_WIDTH            1280
#define SCREEN_HEIGHT           720

#define EXIT_ERROR              1
#define EXIT_SUCCESS            0

#define FPS_DELAY               17

#define PLAYER_DESCENT          0.95
#define PLAYER_SPEED            4
#define PLAYER_BULLET_SPEED     16
#define ALIEN_BULLET_SPEED      4

#define MAX_KEYBOARD_KEYS       350

#define SIDE_PLAYER             0
#define SIDE_ALIEN              1

#define MAX_STARS               500
#define MAX_FIRE_PARTICLES      100
#define MAX_EXPLOSION_PARTICLES 500
#define FRAMES_PER_SECOND       60

#define MAX_SND_CHANNELS        8

enum {
  CH_ANY = -1,
  CH_PLAYER,
  CH_ALIEN_FIRE
};

enum {
  SND_PLAYER_FIRE,
  SND_ALIEN_FIRE,
  SND_PLAYER_DIE,
  SND_ALIEN_DIE,
  SND_MAX
};
