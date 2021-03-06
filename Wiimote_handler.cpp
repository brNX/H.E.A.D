/*
 * Wiimote_handler.cpp
 *
 *  Created on: Apr 13, 2010
 *      Author: bgouveia
 */

#include "Wiimote_handler.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#endif

Wiimote_handler::Wiimote_handler() {
	// TODO Auto-generated constructor stub
	pitch = 0;
	head_align = 0;
	one = false;
	two=false;

}

Wiimote_handler::~Wiimote_handler() {
	// TODO Auto-generated destructor stub
}


/**
 *	@brief Callback that handles an event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *
 *	This function is called automatically by the wiiuse library when an
 *	event occurs on the specified wiimote.
 */
void Wiimote_handler::handle_event(struct wiimote_t* wm) {
	printf("\n\n--- EVENT [id %i] ---\n", wm->unid);

	one = false;
	two = false;

	/* if a button is pressed, report it */
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_A))		printf("A pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_B))		printf("B pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_UP))		printf("UP pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_DOWN))	printf("DOWN pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_LEFT))	printf("LEFT pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_RIGHT))	printf("RIGHT pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_MINUS))	printf("MINUS pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_PLUS))	printf("PLUS pressed\n");
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_ONE)){
		printf("ONE pressed\n");
		one = true;
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_TWO)){
			printf("TWO pressed\n");
			two=true;
	}
	if (IS_PRESSED(wm, WIIMOTE_BUTTON_HOME))	printf("HOME pressed\n");

	/*
	 *	Pressing minus will tell the wiimote we are no longer interested in movement.
	 *	This is useful because it saves battery power.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS))
		wiiuse_motion_sensing(wm, 0);

	/*
	 *	Pressing plus will tell the wiimote we are interested in movement.
	 */
	//if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS));
	
		/*
	 *	Pressing minus will tell the wiimote we are no longer interested in movement.
	 *	This is useful because it saves battery power.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_MINUS))
		wiiuse_motion_sensing(wm, 0);

	/*
	 *	Pressing plus will tell the wiimote we are interested in movement.
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_PLUS))
		wiiuse_motion_sensing(wm, 1);


	/*
	 *	Pressing B will toggle the rumble
	 *
	 *	if B is pressed but is not held, toggle the rumble
	 */
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_B))
		wiiuse_toggle_rumble(wm);

	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_UP))
		wiiuse_set_ir(wm, 1);
	if (IS_JUST_PRESSED(wm, WIIMOTE_BUTTON_DOWN))
		wiiuse_set_ir(wm, 0);

	/* if the accelerometer is turned on then print angles */
	if (WIIUSE_USING_ACC(wm)) {
		printf("wiimote roll  = %f [%f]\n", wm->orient.roll, wm->orient.a_roll);
		printf("wiimote pitch = %f [%f]\n", wm->orient.pitch, wm->orient.a_pitch);
		pitch=wm->orient.a_pitch;
		printf("wiimote yaw   = %f\n", wm->orient.yaw);
	}

	/*
	 *	If IR tracking is enabled then print the coordinates
	 *	on the virtual screen that the wiimote is pointing to.
	 *
	 *	Also make sure that we see at least 1 dot.
	 */
	if (WIIUSE_USING_IR(wm)) {
		int i = 0;
		int num_points = 0;
		int x1, y1, x2, y2;

		/* go through each of the 4 possible IR sources */
		for (; i < 4; ++i) {
			/* check if the source is visible */
			if (wm->ir.dot[i].visible)
				num_points++;
				printf("IR source %i: (%u, %u)\n", i, wm->ir.dot[i].x, wm->ir.dot[i].y);
		}

		if(num_points >= 2){
			if((wm->ir.dot[0].x) < (wm->ir.dot[1].x)){
				x1 = wm->ir.dot[0].x;
				y1 = wm->ir.dot[0].y;
				x2 = wm->ir.dot[1].x;
				y2 = wm->ir.dot[1].y;
			}else{
				x1 = wm->ir.dot[1].x;
				y1 = wm->ir.dot[1].y;
				x2 = wm->ir.dot[0].x;
				y2 = wm->ir.dot[0].y;
			}

			printf("Y diff: %d", y2 - y1);
			head_align = (y2 - y1)/4;
		}

		printf("IR cursor: (%u, %u)\n", wm->ir.x, wm->ir.y);
		printf("IR z distance: %f\n", wm->ir.z);
	}

	/* show events specific to supported expansions */
	if (wm->exp.type == EXP_NUNCHUK) {
		/* nunchuk */
		struct nunchuk_t* nc = (nunchuk_t*)&wm->exp.nunchuk;

		if (IS_PRESSED(nc, NUNCHUK_BUTTON_C))		printf("Nunchuk: C pressed\n");
		if (IS_PRESSED(nc, NUNCHUK_BUTTON_Z))		printf("Nunchuk: Z pressed\n");

		printf("nunchuk roll  = %f\n", nc->orient.roll);
		printf("nunchuk pitch = %f\n", nc->orient.pitch);
		printf("nunchuk yaw   = %f\n", nc->orient.yaw);

		printf("nunchuk joystick angle:     %f\n", nc->js.ang);
		printf("nunchuk joystick magnitude: %f\n", nc->js.mag);
	} else if (wm->exp.type == EXP_CLASSIC) {
		/* classic controller */
		struct classic_ctrl_t* cc = (classic_ctrl_t*)&wm->exp.classic;

		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZL))			printf("Classic: ZL pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_B))			printf("Classic: B pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_Y))			printf("Classic: Y pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_A))			printf("Classic: A pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_X))			printf("Classic: X pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_ZR))			printf("Classic: ZR pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_LEFT))		printf("Classic: LEFT pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_UP))			printf("Classic: UP pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_RIGHT))		printf("Classic: RIGHT pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_DOWN))		printf("Classic: DOWN pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_L))		printf("Classic: FULL L pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_MINUS))		printf("Classic: MINUS pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_HOME))		printf("Classic: HOME pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_PLUS))		printf("Classic: PLUS pressed\n");
		if (IS_PRESSED(cc, CLASSIC_CTRL_BUTTON_FULL_R))		printf("Classic: FULL R pressed\n");

		printf("classic L button pressed:         %f\n", cc->l_shoulder);
		printf("classic R button pressed:         %f\n", cc->r_shoulder);
		printf("classic left joystick angle:      %f\n", cc->ljs.ang);
		printf("classic left joystick magnitude:  %f\n", cc->ljs.mag);
		printf("classic right joystick angle:     %f\n", cc->rjs.ang);
		printf("classic right joystick magnitude: %f\n", cc->rjs.mag);
	} else if (wm->exp.type == EXP_GUITAR_HERO_3) {
		/* guitar hero 3 guitar */
		struct guitar_hero_3_t* gh3 = (guitar_hero_3_t*)&wm->exp.gh3;

		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_UP))		printf("Guitar: Strum Up pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_STRUM_DOWN))	printf("Guitar: Strum Down pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_YELLOW))		printf("Guitar: Yellow pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_GREEN))		printf("Guitar: Green pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_BLUE))			printf("Guitar: Blue pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_RED))			printf("Guitar: Red pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_ORANGE))		printf("Guitar: Orange pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_PLUS))			printf("Guitar: Plus pressed\n");
		if (IS_PRESSED(gh3, GUITAR_HERO_3_BUTTON_MINUS))		printf("Guitar: Minus pressed\n");

		printf("Guitar whammy bar:          %f\n", gh3->whammy_bar);
		printf("Guitar joystick angle:      %f\n", gh3->js.ang);
		printf("Guitar joystick magnitude:  %f\n", gh3->js.mag);
	}
}


/**
 *	@brief Callback that handles a read event.
 *
 *	@param wm		Pointer to a wiimote_t structure.
 *	@param data		Pointer to the filled data block.
 *	@param len		Length in bytes of the data block.
 *
 *	This function is called automatically by the wiiuse library when
 *	the wiimote has returned the full data requested by a previous
 *	call to wiiuse_read_data().
 *
 *	You can read data on the wiimote, such as Mii data, if
 *	you know the offset address and the length.
 *
 *	The \a data pointer was specified on the call to wiiuse_read_data().
 *	At the time of this function being called, it is not safe to deallocate
 *	this buffer.
 */
void Wiimote_handler::handle_read(struct wiimote_t* wm, byte* data, unsigned short len) {
	int i = 0;

	printf("\n\n--- DATA READ [wiimote id %i] ---\n", wm->unid);
	printf("finished read of size %i\n", len);
	for (; i < len; ++i) {
		if (!(i%16))
			printf("\n");
		printf("%x ", data[i]);
	}
	printf("\n\n");
}


/**
 *	@brief Callback that handles a controller status event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *	@param attachment		Is there an attachment? (1 for yes, 0 for no)
 *	@param speaker			Is the speaker enabled? (1 for yes, 0 for no)
 *	@param ir				Is the IR support enabled? (1 for yes, 0 for no)
 *	@param led				What LEDs are lit.
 *	@param battery_level	Battery level, between 0.0 (0%) and 1.0 (100%).
 *
 *	This occurs when either the controller status changed
 *	or the controller status was requested explicitly by
 *	wiiuse_status().
 *
 *	One reason the status can change is if the nunchuk was
 *	inserted or removed from the expansion port.
 */
void Wiimote_handler::handle_ctrl_status(struct wiimote_t* wm) {
	printf("\n\n--- CONTROLLER STATUS [wiimote id %i] ---\n", wm->unid);

	printf("attachment:      %i\n", wm->exp.type);
	printf("speaker:         %i\n", WIIUSE_USING_SPEAKER(wm));
	printf("ir:              %i\n", WIIUSE_USING_IR(wm));
	printf("leds:            %i %i %i %i\n", WIIUSE_IS_LED_SET(wm, 1), WIIUSE_IS_LED_SET(wm, 2), WIIUSE_IS_LED_SET(wm, 3), WIIUSE_IS_LED_SET(wm, 4));
	printf("battery:         %f %%\n", wm->battery_level);
}


/**
 *	@brief Callback that handles a disconnection event.
 *
 *	@param wm				Pointer to a wiimote_t structure.
 *
 *	This can happen if the POWER button is pressed, or
 *	if the connection is interrupted.
 */
void Wiimote_handler::handle_disconnect(wiimote* wm) {
	printf("\n\n--- DISCONNECTED [wiimote id %i] ---\n", wm->unid);
}



void Wiimote_handler::init(){

	wiimotes =  wiiuse_init(MAX_WIIMOTES);

	/*
	 *	Find wiimote devices
	 *
	 *	Now we need to find some wiimotes.
	 *	Give the function the wiimote array we created, and tell it there
	 *	are MAX_WIIMOTES wiimotes we are interested in.
	 *
	 *	Set the timeout to be 5 seconds.
	 *
	 *	This will return the number of actual wiimotes that are in discovery mode.
	 */
	found = wiiuse_find(wiimotes, MAX_WIIMOTES, 5);
	if (!found) {
		printf ("No wiimotes found.");
		exit (-1);
	}

	/*
	 *	Connect to the wiimotes
	 *
	 *	Now that we found some wiimotes, connect to them.
	 *	Give the function the wiimote array and the number
	 *	of wiimote devices we found.
	 *
	 *	This will return the number of established connections to the found wiimotes.
	 */
	connected = wiiuse_connect(wiimotes, MAX_WIIMOTES);
	if (connected)
		printf("Connected to %i wiimotes (of %i found).\n", connected, found);
	else {
		printf("Failed to connect to any wiimote.\n");
		exit (-1);
	}

	/*
	 *	Now set the LEDs and rumble for a second so it's easy
	 *	to tell which wiimotes are connected (just like the wii does).
	 */
	wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
	wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_2);
	wiiuse_set_leds(wiimotes[2], WIIMOTE_LED_3);
	wiiuse_set_leds(wiimotes[3], WIIMOTE_LED_4);
	wiiuse_rumble(wiimotes[0], 1);
	wiiuse_rumble(wiimotes[1], 1);

#ifndef WIN32
	usleep(200000);
#else
	Sleep(200);
#endif

	wiiuse_rumble(wiimotes[0], 0);
	wiiuse_rumble(wiimotes[1], 0);
	//wiiuse_motion_sensing(wiimotes[0], 1);

}

void Wiimote_handler::poll(){
	if (wiiuse_poll(wiimotes, MAX_WIIMOTES)) {
		/*
		 *	This happens if something happened on any wiimote.
		 *	So go through each one and check if anything happened.
		 */
		int i = 0;
		for (; i < MAX_WIIMOTES; ++i) {
			switch (wiimotes[i]->event) {
			case WIIUSE_EVENT:
				/* a generic event occured */
				handle_event(wiimotes[i]);
				break;

			case WIIUSE_STATUS:
				/* a status event occured */
				handle_ctrl_status(wiimotes[i]);
				break;

			case WIIUSE_DISCONNECT:
			case WIIUSE_UNEXPECTED_DISCONNECT:
				/* the wiimote disconnected */
				handle_disconnect(wiimotes[i]);
				break;

			case WIIUSE_READ_DATA:
				/*
				 *	Data we requested to read was returned.
				 *	Take a look at wiimotes[i]->read_req
				 *	for the data.
				 */
				break;

			case WIIUSE_NUNCHUK_INSERTED:
				/*
				 *	a nunchuk was inserted
				 *	This is a good place to set any nunchuk specific
				 *	threshold values.  By default they are the same
				 *	as the wiimote.
				 */
				//wiiuse_set_nunchuk_orient_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 90.0f);
				//wiiuse_set_nunchuk_accel_threshold((struct nunchuk_t*)&wiimotes[i]->exp.nunchuk, 100);
				printf("Nunchuk inserted.\n");
				break;

			case WIIUSE_CLASSIC_CTRL_INSERTED:
				printf("Classic controller inserted.\n");
				break;

			case WIIUSE_GUITAR_HERO_3_CTRL_INSERTED:
				/* some expansion was inserted */
				handle_ctrl_status(wiimotes[i]);
				printf("Guitar Hero 3 controller inserted.\n");
				break;

			case WIIUSE_NUNCHUK_REMOVED:
			case WIIUSE_CLASSIC_CTRL_REMOVED:
			case WIIUSE_GUITAR_HERO_3_CTRL_REMOVED:
				/* some expansion was removed */
				handle_ctrl_status(wiimotes[i]);
				printf("An expansion was removed.\n");
				break;

			default:
				break;
			}
		}
	}
}


void Wiimote_handler::release(){
	wiiuse_cleanup(wiimotes, MAX_WIIMOTES);
}
