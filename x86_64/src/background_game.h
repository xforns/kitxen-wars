#ifndef BACKGROUND_GAME_H
#define BACKGROUND_GAME_H

#include <OpenGL/OpenGL.h>
#include <ctime>

#include "asset_helper.h"
#include "defs.h"
#include "messaging.h"
#include "observer.h"

using namespace std;

class background_game : public observer 
{

private:
	
	static GLuint _bg1, _bg2;
	
	static double _bg_y1, _bg_y2;
	
	static clock_t _last_clock;
	
	pthread_t thread;
	
	static bool _cancel_thread;
	
public:
	
	background_game();
	~background_game();
	
	void start();
	void stop();
	
	// Static method called launched in a new thread.
	// Params:
	//  void *: nothing in this case is being passed in.
	static void *t_update(void *);
	
	void draw();
	virtual void update(const observable_data &param);
	
};

#endif /* BACKGROUND_GAME_H */