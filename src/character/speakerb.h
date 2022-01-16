/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_SPEAKERB_H
#define PSXF_GUARD_SPEAKERB_H

#include "../gfx.h"
#include "../fixed.h"

//Speaker structure
typedef struct
{
	//Speaker state
	Gfx_Tex tex;
	fixed_t bump;
} speakerb;

//Speaker functions
void speakerb_Init(speakerb *this);
void speakerb_Bump(speakerb *this);
void speakerb_Tick(speakerb *this, fixed_t x, fixed_t y, fixed_t parallax);

#endif
