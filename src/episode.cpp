#include "episode.h"


/****************************************************************

							public

****************************************************************/


episode::episode()
{
	_current_episode_status = NOT_INITIALIZED;
}


episode::~episode()
{
	
}


void episode::start()
{
	_current_episode_status = PLAYING;
}


void episode::stop()
{
	_current_episode_status = ENDED;
}


void episode::pause()
{
	_current_episode_status = PAUSED;
}


episode::_episode_status episode::get_episode_status()
{
	return _current_episode_status;
}


/****************************************************************

							private

****************************************************************/
