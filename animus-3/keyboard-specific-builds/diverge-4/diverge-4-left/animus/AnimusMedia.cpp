/*
  Keyboard.cpp

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

#include "AnimusMedia.h"

#if defined(_USING_HID)

//================================================================================
//================================================================================
//        REMOTE

static const uint8_t _hidReportDescriptor[] PROGMEM =
{

  /* Cross-platform support for controls found on IR Remotes */

  0x05, 0x0c,                    //        Usage Page (Consumer Devices)
  0x09, 0x01,                    //        Usage (Consumer Control)
  0xa1, 0x01,                    //        Collection (Application)
  0x85, 0x05,                    //        REPORT_ID (5)
  0x15, 0x00,                    //        Logical Minimum (0)
  0x25, 0x01,                    //        Logical Maximum (1)
  0x09, 0xe9,                    //        Usage (Volume Up)
  0x09, 0xea,                    //        Usage (Volume Down)
  0x75, 0x01,                    //        Report Size (1)
  0x95, 0x02,                    //        Report Count (2)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xe2,                    //        Usage (Mute)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb0,                    //        Usage (Play)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb1,                    //        Usage (Pause)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb7,                    //        Usage (Stop)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb5,                    //        Usage (Next)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb6,                    //        Usage (Previous)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb3,                    //        Usage (Fast Forward)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x09, 0xb4,                    //        Usage (Rewind)
  0x95, 0x01,                    //        Report Count (1)
  0x81, 0x06,                    //        Input (Data, Variable, Relative)

  0x95, 0x06,                    //        Report Count (6) Number of bits remaining in byte
  0x81, 0x07,                    //        Input (Constant, Variable, Relative)
  0xc0                           //        End Collection
};
//================================================================================
//================================================================================
//        Remote

Remote_::Remote_(void)
{
  static HIDSubDescriptor node(_hidReportDescriptor, sizeof(_hidReportDescriptor));
  HID().AppendDescriptor(&node);
}

void Remote_::begin(void)
{
}

void Remote_::end(void)
{
}

void Remote_::increase(void)
{
  uint8_t m[2];
  m[0] = VOLUME_UP;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::decrease(void)
{
  uint8_t m[2];
  m[0] = VOLUME_DOWN;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::mute(void)
{
  uint8_t m[2];
  m[0] = VOLUME_MUTE;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::play(void)
{
  uint8_t m[2];
  m[0] = REMOTE_PLAY;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::pause(void)
{
  uint8_t m[2];
  m[0] = REMOTE_PAUSE;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::stop(void)
{
  uint8_t m[2];
  m[0] = REMOTE_STOP;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::next(void)
{
  uint8_t m[2];
  m[0] = REMOTE_NEXT;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::previous(void)
{
  uint8_t m[2];
  m[0] = REMOTE_PREVIOUS;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

void Remote_::forward(void)
{
  uint8_t m[2];
  m[0] = 0;
  m[1] = REMOTE_FAST_FORWARD >> 8;
  HID().SendReport(5,m,2);
}

void Remote_::rewind(void)
{
  uint8_t m[2];
  m[0] = 0;
  m[1] = REMOTE_REWIND >> 8;
  HID().SendReport(5,m,2);
}

void Remote_::clear(void)
{
  uint8_t m[2];
  m[0] = 0;
  m[1] = 0;
  HID().SendReport(5,m,2);
}

Remote_ Remote;

#endif
