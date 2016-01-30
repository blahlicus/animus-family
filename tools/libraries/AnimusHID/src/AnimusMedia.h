/*
  Keyboard.h

  Copyright (c) 2015, Arduino LLC
  Original code (pre-library): Copyright (c) 2011, Peter Barrett

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef ANIMUSMEDIA_h
#define ANIMUSMEDIA_h

#include "HID.h"

#if !defined(_USING_HID)

#warning "Using legacy HID core (non pluggable)"

#else

// ---------MEDIA-------------

#define REMOTE_CLEAR 0
#define VOLUME_UP 1
#define VOLUME_DOWN 2
#define VOLUME_MUTE 4
#define REMOTE_PLAY 8
#define REMOTE_PAUSE 16
#define REMOTE_STOP 32
#define REMOTE_NEXT 64
#define REMOTE_PREVIOUS 128
#define REMOTE_FAST_FORWARD 256
#define REMOTE_REWIND 512

class Remote_
{
private:
public:
	Remote_(void);
	void begin(void);
	void end(void);

	// Volume
	void increase(void);
	void decrease(void);
	void mute(void);

	// Playback
	void play(void);
	void pause(void);
	void stop(void);

	// Track Controls
	void next(void);
	void previous(void);
	void forward(void);
	void rewind(void);

	// Send an empty report to prevent repeated actions
	void clear(void);
};
extern Remote_ Remote;

#endif
#endif
