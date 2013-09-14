#ifndef EPISODE_MENU_H
#define EPISODE_MENU_H

#include <OpenGL/OpenGL.h>
#include <map>
#include <string>
#include <cstdio>
#include <ctime>

#include "episode.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"

using namespace std;

class episode_menu : public episode
{

private:
	
	GLuint _bg;
	
public:
	
	episode_menu();
	~episode_menu();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	virtual void mouse(uint32_t status, int x, int y);
};

#endif /* EPISODE_MENU_H */