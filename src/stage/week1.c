/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week1.h"

#include "../archive.h"
#include "../mem.h"
#include "../stage.h"

//Week 1 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //back
	Gfx_Tex tex_back1; //back zad
	Gfx_Tex tex_back2; //grass
	Gfx_Tex tex_back3; //grass zad

} Back_Week1;

void Back_Week1_DrawFG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy;	

	if (stage.stage_id == StageId_1_1 && stage.song_step >= 602 && stage.song_step <= 607) {
	//Draw white
	RECT white_src = {25, 56, 3, 3};
	RECT_FIXED white_dst = {
		FIXED_DEC(-170,1),
		FIXED_DEC(-125,1),
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &white_src, &white_dst, stage.camera.bzoom);
	}

	if (stage.stage_id == StageId_1_1 && stage.song_step >= 528 && stage.song_step <= 607) {
	//Draw black
	RECT black_src = {0, 235, 1, 1};
	RECT_FIXED black_dst = {
		FIXED_DEC(-170,1),
		FIXED_DEC(-125,1),
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &black_src, &black_dst, stage.camera.bzoom);
	}
}

//Week 1 background functions
void Back_Week1_DrawBG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy;	

	if (stage.stage_id == StageId_1_1 && stage.song_step >= 547) {
	//Draw grass zad
	fx = stage.camera.x;
	fy = stage.camera.y;

	RECT grassz_src = {0, 0, 255, 255};
	RECT_FIXED grassz_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back3, &grassz_src, &grassz_dst, stage.camera.bzoom);
	}

	if (stage.stage_id == StageId_1_1 && stage.song_step < 547) {
	//Draw grass
	fx = stage.camera.x;
	fy = stage.camera.y;

	RECT grass_src = {0, 0, 255, 255};
	RECT_FIXED grass_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back2, &grass_src, &grass_dst, stage.camera.bzoom);
	}

	if (stage.stage_id == StageId_1_1 && stage.song_step >= 547) {
	//Draw back zad
	fx = stage.camera.x * 8 / 10;
	fy = stage.camera.y * 8 / 10;
	
	RECT bgz_src = {0, 0, 255, 255};
	RECT_FIXED bgz_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &bgz_src, &bgz_dst, stage.camera.bzoom);
	}

	if (stage.stage_id == StageId_1_1 && stage.song_step < 547) {
	//Draw back
	fx = stage.camera.x * 8 / 10;
	fy = stage.camera.y * 8 / 10;
	
	RECT bg_src = {0, 0, 255, 255};
	RECT_FIXED bg_dst = {
		FIXED_DEC(-170,1) - fx,
		FIXED_DEC(-125,1) - fy,
		FIXED_DEC(500,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &bg_src, &bg_dst, stage.camera.bzoom);
	}
}

void Back_Week1_Free(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week1_New(void)
{
	//Allocate background structure
	Back_Week1 *this = (Back_Week1*)Mem_Alloc(sizeof(Back_Week1));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = Back_Week1_DrawFG;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week1_DrawBG;
	this->back.free = Back_Week1_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK1\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
