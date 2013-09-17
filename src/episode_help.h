#ifndef EPISODE_HELP_H
#define EPISODE_HELP_H

#include <OpenGL/OpenGL.h>
#include <map>
#include <string>
#include <cstdio>
#include <ctime>

#include "episode.h"
#include "observer.h"
#include "messaging.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"

using namespace std;

class episode_help : public episode, public observer
{

private:
	
	GLuint _bg;
	
public:
	
	episode_help();
	~episode_help();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	
	virtual void update(const observable_data &param);
};

#endif /* EPISODE_HELP_H */