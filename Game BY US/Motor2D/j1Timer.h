#ifndef __j1TIMER_H__
#define __j1TIMER_H__

#include "p2Defs.h"

class j1Timer
{
public:

	// Constructor
	j1Timer();

	void Start();
	uint Read() const;
	float ReadSec() const;

private:
	uint	started_at;
};

#endif //__j1TIMER_H__