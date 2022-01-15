/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week3.h"

#include "../mem.h"
#include "../archive.h"
#include "../random.h"
#include "../timer.h"

int swapfard;

//Week 3 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //bg1
	Gfx_Tex tex_back1; //bg2
	Gfx_Tex tex_back2; //bg3
	Gfx_Tex tex_back3; //bg4
	Gfx_Tex tex_stage; //lil thing idk what to call stage thing
	
} Back_Week3;

void Back_Week3_DrawBG(StageBack *back)
{
	Back_Week3 *this = (Back_Week3*)back;
	
	fixed_t fx, fy;

	swapfard++;

	if (swapfard == 40)
	{
	  swapfard = 0;
	  swapfard++;
	}
	//Draw stage
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT stage_src = {0, 0, 256, 256};
	RECT_FIXED stage_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};	

	Stage_DrawTex(&this->tex_stage, &stage_src, &stage_dst, stage.camera.bzoom);



	//Draw back
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT back0_src = {0, 0, 256, 256};
	RECT_FIXED back0_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};	
	//Draw back
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT back1_src = {0, 0, 256, 256};
	RECT_FIXED back1_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};	
	//Draw back
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT back2_src = {0, 0, 256, 256};
	RECT_FIXED back2_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};	
	//Draw back
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT back3_src = {0, 0, 256, 256};
	RECT_FIXED back3_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};	

	//Animate and draw bg
	fx = stage.camera.x;
	fy = stage.camera.y;
	
		switch (swapfard)
		{
			case 0:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 1:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 2:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 3:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 4:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 5:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 6:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
		    case 7:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 8:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 9:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 10:
				Stage_DrawTex(&this->tex_back1, &back1_src, &back1_dst, stage.camera.bzoom);
				break;
			case 11:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 12:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 13:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 14:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 15:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 16:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 17:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 18:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 19:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 20:
				Stage_DrawTex(&this->tex_back2, &back2_src, &back2_dst, stage.camera.bzoom);
				break;
			case 21:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 22:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
	    	case 23:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 24:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 25:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 26:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 27:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 28:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 29:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 30:
				Stage_DrawTex(&this->tex_back3, &back3_src, &back3_dst, stage.camera.bzoom);
				break;
			case 31:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 32:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 33:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 34:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 35:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 36:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 37:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 38:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
		    case 39:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			case 40:
				Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
			default:
			   Stage_DrawTex(&this->tex_back0, &back0_src, &back0_dst, stage.camera.bzoom);
				break;
		}
}

void Back_Week3_Free(StageBack *back)
{
	Back_Week3 *this = (Back_Week3*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week3_New(void)
{
	//Allocate background structure
	Back_Week3 *this = (Back_Week3*)Mem_Alloc(sizeof(Back_Week3));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week3_DrawBG;
	this->back.free = Back_Week3_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK3\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Gfx_LoadTex(&this->tex_stage, Archive_Find(arc_back, "back4.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
