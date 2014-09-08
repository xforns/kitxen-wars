#ifndef EPISODE_END_H
#define EPISODE_END_H

#include <map>
#include <string>
#include <cstdio>
#include <ctime>

#include "gl_helper.h"
#include "episode.h"
#include "observer.h"
#include "messaging.h"
#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"

using namespace std;

class episode_end : public episode, public observer
{

private:
	
	GLuint _bg;
	
	clock_t _last_clock;
	
public:
	
	episode_end();
	~episode_end();
	
	virtual void start();
	virtual void stop();
	virtual void pause();
	virtual void update();
	virtual void draw();
	
	virtual void update(const observable_data &param);
};

#endif /* EPISODE_END_H */