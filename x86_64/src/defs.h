#ifndef DEFS_H
#define DEFS_H

#define MB_LEFT   0
#define MB_MIDDLE 1
#define MB_RIGHT  2
#define LMB_PRESSED (1<<0)
#define MMB_PRESSED (1<<1)
#define RMB_PRESSED (1<<2)
#define LMB_CLICKED (1<<16)
#define MMB_CLICKED (1<<17)
#define RMB_CLICKED (1<<18)
#define MB_PRESSED(state, button) (1<<(button))
#define MB_CLICKED(state, button) (1<<((button)+16))
#define MB_MASK_PRESSED 0x0000ffffL
#define MB_MASK_CLICKED 0xffff0000L

#define MSG_MOUSE 0
#define MSG_EPISODE 1
#define MSG_KEYBOARD 2
#define MSG_KEYBOARD_S 3
#define MSG_COLLISION 4

#define EPISODE_SPLASH 0
#define EPISODE_MENU 1
#define EPISODE_GAME 2
#define EPISODE_HELP 3
#define EPISODE_GAMEOVER 4
#define EPISODE_EXIT 5

#define COLLISION_NONE 0
#define COLLISION_LEFT (1<<1)
#define COLLISION_RIGHT (1<<3)
#define COLLISION_TOP (1<<4)
#define COLLISION_BOTTOM (1<<2)

// timesteps
#define TIME_STEP_BG 5000


#include <string>

struct observable_data {
	
	int msg_type;
	int a;
	int b;
	int c;
	std::string d;
};

struct pt {
	
	double x;
	double y;
};

enum entity_type { TYPE_NONE , TYPE_CHARACTER, TYPE_ENEMY, TYPE_BULLET, TYPE_BOMB };


#endif /* DEFS_H */