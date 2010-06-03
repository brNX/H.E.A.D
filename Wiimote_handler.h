/*
 * Wiimote_handler.h
 *
 *  Created on: Apr 13, 2010
 *      Author: bgouveia
 */

#ifndef WIIMOTE_HANDLER_H_
#define WIIMOTE_HANDLER_H_

#include <wiiuse.h>

#define MAX_WIIMOTES 4

class Wiimote_handler {
public:
	Wiimote_handler();
	virtual ~Wiimote_handler();
	void init();
	void release();
	void poll();
	inline float getPitch(){return pitch;}
	inline bool getOne(){return one;}
	inline bool getTwo(){return two;}
	inline float getHead(){return head_align;}
private:
	void handle_event(struct wiimote_t* wm);
	void handle_read(struct wiimote_t* wm, byte* data, unsigned short len);
	void handle_ctrl_status(struct wiimote_t* wm);
	void handle_disconnect(wiimote* wm);

private:
	wiimote** wiimotes;
	int found, connected;
	float pitch;
	float head_align;
	bool one, two;


};

#endif /* WIIMOTE_HANDLER_H_ */
