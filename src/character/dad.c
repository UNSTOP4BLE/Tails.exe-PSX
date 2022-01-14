/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "dad.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//Dad character structure
enum
{
	Dad_ArcMain_Idle0,
	Dad_ArcMain_Idle1,
	Dad_ArcMain_Left0,
	Dad_ArcMain_Left1,
	Dad_ArcMain_Down,
	Dad_ArcMain_Up0,
	Dad_ArcMain_Up1,
	Dad_ArcMain_Right0,
	Dad_ArcMain_Right1,

	Dad_ArcMain_Idleb0,
	Dad_ArcMain_Idleb1,
	Dad_ArcMain_Leftb,
	Dad_ArcMain_Downb,
	Dad_ArcMain_Upb,
	Dad_ArcMain_Rightb,
	
	Dad_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Dad_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_Dad;

//Dad character definitions
static const CharFrame char_dad_frame[] = {
	{Dad_ArcMain_Idle0, {  0,   0, 77, 103}, { 65, 103}},  //0 idle 1
	{Dad_ArcMain_Idle0, { 77,   0, 76, 103}, { 64, 103}},  //1 idle 2
	{Dad_ArcMain_Idle0, {153,   0, 75, 103}, { 64, 103}},  //2 idle 3
	{Dad_ArcMain_Idle0, {  0, 103, 78, 103}, { 67, 103}},  //3 idle 4
	{Dad_ArcMain_Idle0, { 78, 103, 79, 103}, { 67, 103}},  //4 idle 5
	{Dad_ArcMain_Idle0, {157, 103, 78, 103}, { 67, 103}},  //5 idle 6
	{Dad_ArcMain_Idle1, {  0,   0, 78, 103}, { 67, 103}},  //6 idle 7
	{Dad_ArcMain_Idle1, { 78,   0, 78, 103}, { 67, 103}},  //7 idle 8
	{Dad_ArcMain_Idle1, {  0, 103, 76, 103}, { 64, 103}},  //8 idle 9
	{Dad_ArcMain_Idle1, { 76, 103, 76, 103}, { 65, 103}},  //9 idle 10
	
	{Dad_ArcMain_Left0, {  0,   0, 101, 97}, { 101, 97}},  //10 left 1
	{Dad_ArcMain_Left0, {101,   0, 100, 99}, { 100, 99}},  //11 left 2
	{Dad_ArcMain_Left0, {  0,  97, 100, 100}, { 100, 99}},  //12 left 3
	{Dad_ArcMain_Left0, {100,  99, 100, 100}, { 100, 100}},  //13 left 4
	{Dad_ArcMain_Left1, {  0,   0, 100, 100}, { 100, 100}},  //14 left 5
	{Dad_ArcMain_Left1, {100,   0, 100, 100}, { 100, 100}},  //15 left 6

	{Dad_ArcMain_Down, {  0,   0, 84, 90}, { 83, 89}},  //16 down 1
	{Dad_ArcMain_Down, { 84,   0, 85, 90}, { 84, 90}},  //17 down 2
	{Dad_ArcMain_Down, {169,   0, 85, 91}, { 84, 90}},  //18 down 3
	{Dad_ArcMain_Down, {  0,  90, 84, 91}, { 83, 91}},  //19 down 4
	{Dad_ArcMain_Down, { 84,  90, 85, 91}, { 83, 91}},  //20 down 5
	{Dad_ArcMain_Down, {169,  91, 85, 91}, { 83, 91}},  //21 down 6
	
	{Dad_ArcMain_Up0, {  0,   0, 88, 113}, { 70, 113}},  //22 up 1
	{Dad_ArcMain_Up0, { 88,   0, 89, 112}, { 70, 112}},  //23 up 2
	{Dad_ArcMain_Up0, {  0, 113, 90, 111}, { 71, 111}},  //24 up 3
	{Dad_ArcMain_Up0, { 90, 112, 90, 111}, { 71, 111}},  //25 up 4
	{Dad_ArcMain_Up1, {  0,   0, 90, 111}, { 72, 111}},  //26 up 5
	{Dad_ArcMain_Up1, { 90,   0, 90, 110}, { 72, 110}},  //27 up 6
	
	{Dad_ArcMain_Right0, {  0,   0, 93, 99}, { 80, 99}},  //28 right 1
	{Dad_ArcMain_Right0, { 93,   0, 91, 98}, { 81, 98}},  //29 right 2
	{Dad_ArcMain_Right0, {  0,  99, 91, 98}, { 81, 98}},  //30 right 3
	{Dad_ArcMain_Right0, { 91,  98, 92, 98}, { 82, 98}},  //31 right 4
	{Dad_ArcMain_Right1, {  0,   0, 92, 99}, { 81, 98}},  //32 right 5
	{Dad_ArcMain_Right1, { 92,   0, 92, 99}, { 81, 98}},  //33 right 6



	{Dad_ArcMain_Idleb0, {  0,   0, 64, 103}, { 53, 103}},  //34 idle 1
	{Dad_ArcMain_Idleb0, { 64,   0, 64, 103}, { 52, 103}},  //35 idle 2
	{Dad_ArcMain_Idleb0, {128,   0, 63, 103}, { 52, 103}},  //36 idle 3
	{Dad_ArcMain_Idleb0, {191,   0, 65, 103}, { 54, 103}},  //37 idle 4
	{Dad_ArcMain_Idleb0, {  0, 103, 65, 103}, { 54, 103}},  //38 idle 5
	{Dad_ArcMain_Idleb0, { 65, 103, 65, 103}, { 54, 103}},  //39 idle 6
	{Dad_ArcMain_Idleb0, {130, 103, 65, 103}, { 54, 103}},  //40 idle 7
	{Dad_ArcMain_Idleb1, {  0,   0, 65, 103}, { 54, 103}},  //41 idle 8
	{Dad_ArcMain_Idleb1, { 65,   0, 65, 103}, { 54, 103}},  //42 idle 9
	{Dad_ArcMain_Idleb1, {130,   0, 65, 103}, { 53, 103}},  //43 idle 10
	
	{Dad_ArcMain_Leftb, {  0,   0, 87, 99}, { 87, 99}},  //44 left 1
	{Dad_ArcMain_Leftb, { 87,   0, 85, 100}, { 85, 99}},  //45 left 2
	{Dad_ArcMain_Leftb, {172,   0, 84, 100}, { 84, 100}},  //46 left 3
	{Dad_ArcMain_Leftb, {  0,  99, 86, 100}, { 86, 100}},  //47 left 4
	{Dad_ArcMain_Leftb, { 86, 100, 85, 100}, { 85, 100}},  //48 left 5
	{Dad_ArcMain_Leftb, {171, 100, 85, 100}, { 85, 100}},  //49 left 6

	{Dad_ArcMain_Downb, {  0,   0, 74, 88}, { 74, 88}},  //50 down 1
	{Dad_ArcMain_Downb, { 74,   0, 73, 89}, { 73, 89}},  //51 down 2
	{Dad_ArcMain_Downb, {147,   0, 74, 90}, { 74, 90}},  //52 down 3
	{Dad_ArcMain_Downb, {  0,  88, 74, 90}, { 74, 90}},  //53 down 4
	{Dad_ArcMain_Downb, { 74,  89, 74, 90}, { 73, 90}},  //54 down 5
	{Dad_ArcMain_Downb, {148,  90, 74, 90}, { 73, 90}},  //55 down 6
	
	{Dad_ArcMain_Upb, {  0,   0, 76, 113}, { 57, 113}},  //56 up 1
	{Dad_ArcMain_Upb, { 76,   0, 76, 112}, { 57, 112}},  //57 up 2
	{Dad_ArcMain_Upb, {152,   0, 77, 111}, { 58, 111}},  //58 up 3
	{Dad_ArcMain_Upb, {  0, 113, 78, 111}, { 59, 111}},  //59 up 4
	{Dad_ArcMain_Upb, { 78, 112, 78, 110}, { 59, 110}},  //60 up 5
	{Dad_ArcMain_Upb, {156, 111, 78, 110}, { 59, 110}},  //61 up 6
	
	{Dad_ArcMain_Rightb, {  0,   0, 83, 99}, { 70, 99}},  //62 right 1
	{Dad_ArcMain_Rightb, { 83,   0, 80, 99}, { 70, 99}},  //63 right 2
	{Dad_ArcMain_Rightb, {163,   0, 80, 97}, { 70, 97}},  //64 right 3
	{Dad_ArcMain_Rightb, {  0,  99, 81, 97}, { 70, 97}},  //65 right 4
	{Dad_ArcMain_Rightb, { 81,  99, 81, 97}, { 70, 97}},  //66 right 5
	{Dad_ArcMain_Rightb, {162,  97, 81, 97}, { 70, 97}},  //67 right 6
};

static const Animation char_dad_anim[CharAnim_Max] = {
	{2, (const u8[]){ 1, 2, 3, 4, 5, 6, 7, 8, 9, ASCR_BACK, 0}}, //CharAnim_Idle
	{2, (const u8[]){ 10, 11, 12, 13, 14, 15, ASCR_BACK, 0}},         //CharAnim_Left
	{2, (const u8[]){ 10, 11, 12, 13, 14, 15, ASCR_BACK, 0}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 16, 17, 18, 19, 20, 21, ASCR_BACK, 0}},         //CharAnim_Down
	{2, (const u8[]){ 16, 17, 18, 19, 20, 21, ASCR_BACK, 0}},   //CharAnim_DownAlt
	{2, (const u8[]){ 22, 23, 24, 25, 26, 27, ASCR_BACK, 0}},         //CharAnim_Up
	{2, (const u8[]){ 22, 23, 24, 25, 26, 27, ASCR_BACK, 0}},   //CharAnim_UpAlt
	{2, (const u8[]){ 28, 29, 30, 31, 32, 33, ASCR_BACK, 0}},         //CharAnim_Right
	{2, (const u8[]){ 28, 29, 30, 31, 32, 33, ASCR_BACK, 0}},   //CharAnim_RightAlt
};

static const Animation char_dad_animb[CharAnim_Max] = {
	{2, (const u8[]){ 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, ASCR_BACK, 0}}, //CharAnim_Idle
	{2, (const u8[]){ 44, 45, 46, 47, 48, 49, ASCR_BACK, 0}},         //CharAnim_Left
	{2, (const u8[]){ 44, 45, 46, 47, 48, 49, ASCR_BACK, 0}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 50, 51, 52, 53, 54, 55, ASCR_BACK, 0}},         //CharAnim_Down
	{2, (const u8[]){ 50, 51, 52, 53, 54, 55, ASCR_BACK, 0}},   //CharAnim_DownAlt
	{2, (const u8[]){ 56, 57, 58, 59, 60, 61, ASCR_BACK, 0}},         //CharAnim_Up
	{2, (const u8[]){ 56, 57, 58, 59, 60, 61, ASCR_BACK, 0}},   //CharAnim_UpAlt
	{2, (const u8[]){ 62, 63, 64, 65, 66, 67, ASCR_BACK, 0}},         //CharAnim_Right
	{2, (const u8[]){ 62, 63, 64, 65, 66, 67, ASCR_BACK, 0}},   //CharAnim_RightAlt
};
//Dad character functions
void Char_Dad_SetFrame(void *user, u8 frame)
{
	Char_Dad *this = (Char_Dad*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_dad_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_Dad_Tick(Character *character)
{
	Char_Dad *this = (Char_Dad*)character;
	
	if (stage.stage_id == StageId_1_1 && stage.song_step >= 607)
		this->character.health_i = 2;


	if (stage.stage_id == StageId_1_1 && stage.song_step > 1119) {
		this->character.focus_x = FIXED_DEC(0,1);
		this->character.focus_y = FIXED_DEC(-75,1);
		this->character.focus_zoom = FIXED_DEC(17,10);
	}
	if (stage.stage_id == StageId_1_1 && stage.song_step > 1130) {
		this->character.focus_x = FIXED_DEC(55,1);
		this->character.focus_y = FIXED_DEC(-75,1);
		this->character.focus_zoom = FIXED_DEC(1,1);
	}

	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	if (stage.stage_id == StageId_1_1 && stage.song_step < 547)
		Animatable_Animate(&character->animatable, (void*)this, Char_Dad_SetFrame);
	else if (stage.stage_id == StageId_1_1 && stage.song_step >= 547)
		Animatable_Animate(&character->animatableb, (void*)this, Char_Dad_SetFrame);
	else
	   Animatable_Animate(&character->animatableb, (void*)this, Char_Dad_SetFrame);

	Character_Draw(character, &this->tex, &char_dad_frame[this->frame]);
}

void Char_Dad_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Animatable_SetAnim(&character->animatableb, anim);
	Character_CheckStartSing(character);
}

void Char_Dad_Free(Character *character)
{
	Char_Dad *this = (Char_Dad*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Dad_New(fixed_t x, fixed_t y)
{
	//Allocate dad object
	Char_Dad *this = Mem_Alloc(sizeof(Char_Dad));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Dad_New] Failed to allocate dad object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Dad_Tick;
	this->character.set_anim = Char_Dad_SetAnim;
	this->character.free = Char_Dad_Free;
	
	Animatable_Init(&this->character.animatable, char_dad_anim);
	Animatable_Init(&this->character.animatableb, char_dad_animb);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	if (stage.stage_id == StageId_1_2)
		this->character.health_i = 2;
	else
		this->character.health_i = 1;

	this->character.focus_x = FIXED_DEC(55,1);
	this->character.focus_y = FIXED_DEC(-75,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\DAD.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //Dad_ArcMain_Idle0
		"idle1.tim", //Dad_ArcMain_Idle1
		"left0.tim",  //Dad_ArcMain_Left
		"left1.tim",  //Dad_ArcMain_Left
		"down.tim",  //Dad_ArcMain_Down
		"up0.tim",    //Dad_ArcMain_Up
		"up1.tim",    //Dad_ArcMain_Up
		"right0.tim", //Dad_ArcMain_Right
		"right1.tim", //Dad_ArcMain_Right

		"idleb0.tim", //Dad_ArcMain_Idle0
		"idleb1.tim", //Dad_ArcMain_Idle1
		"leftb.tim",  //Dad_ArcMain_Left
		"downb.tim",  //Dad_ArcMain_Down
		"upb.tim",    //Dad_ArcMain_Up
		"rightb.tim", //Dad_ArcMain_Right
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
