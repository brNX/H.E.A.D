/*
 * Goal.h
 *
 *  Created on: Apr 29, 2010
 *      Author: bgouveia
 */

#ifndef GOAL_H_
#define GOAL_H_

#include "PhysicalObject.h"

class Goal: public PhysicalObject {
public:
	Goal();
	Goal(float x, float y);
	~Goal();
public:
	void draw();
	void handleevents();
};

#endif /* GOAL_H_ */
