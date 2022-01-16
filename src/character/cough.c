/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "cough.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//cough character structure
enum
{
	cough_ArcMain_Idle,
	cough_ArcMain_Left,
	cough_ArcMain_Down,
	cough_ArcMain_Up,
	cough_ArcMain_Right,
	
	cough_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[cough_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_cough;

//cough character definitions
static const CharFrame char_cough_frame[] = {
	{cough_ArcMain_Idle, {  0,   0, 115, 92}, { 112, 92}},  //0 idle 1
	{cough_ArcMain_Idle, {115,   0, 112, 93}, { 109, 92}},  //1 idle 2
	{cough_ArcMain_Idle, {  0,  92, 110, 96}, { 107, 96}},  //2 idle 3
	{cough_ArcMain_Idle, {110,  93, 105, 99}, { 103, 99}},  //3 idle 4
	
	{cough_ArcMain_Left, {  0,   0, 105, 106}, { 102, 106}},  //4 left 1
	{cough_ArcMain_Left, {105,   0, 104, 111}, { 104, 111}},  //5 left 2
	{cough_ArcMain_Left, {  0, 106, 107, 117}, { 107, 117}},  //6 left 3
	{cough_ArcMain_Left, {107, 111, 112, 120}, { 112, 120}},  //7 left 4

	{cough_ArcMain_Down, {  0,   0, 104, 107}, { 102, 107}},  //8 down 1
	{cough_ArcMain_Down, {104,   0, 111, 105}, { 108, 105}},  //9 down 2
	{cough_ArcMain_Down, {  0, 107, 115, 101}, { 112, 101}},  //10 down 3
	{cough_ArcMain_Down, {115, 105, 118, 101}, { 115, 101}},  //11 down 4
	
	{cough_ArcMain_Up, {  0,   0, 105, 106}, { 102, 106}},  //12 up 1
	{cough_ArcMain_Up, {105,   0, 105, 111}, { 102, 111}},  //13 up 2
	{cough_ArcMain_Up, {  0, 106, 105, 117}, { 102, 117}},  //14 up 3
	{cough_ArcMain_Up, {105, 111, 104, 120}, { 102, 120}},  //15 up 4
	
	{cough_ArcMain_Right, {  0,   0, 105, 106}, { 102, 106}},  //16 right 1
	{cough_ArcMain_Right, {105,   0, 106, 111}, { 100, 111}},  //17 right 2
	{cough_ArcMain_Right, {  0, 106, 105, 117}, { 98, 117}},  //18 right 3
	{cough_ArcMain_Right, {105, 111, 108, 120}, { 95, 120}},  //19 right 4
};

static const Animation char_cough_anim[CharAnim_Max] = {
	{2, (const u8[]){ 0, 1, 2, 3, ASCR_BACK, 0}}, //CharAnim_Idle
	{2, (const u8[]){ 4, 5, 6, 7, ASCR_BACK, 0}},         //CharAnim_Left
	{2, (const u8[]){ 4, 5, 6, 7, ASCR_BACK, 0}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 8, 9, 10, 11, ASCR_BACK, 0}},         //CharAnim_Down
	{2, (const u8[]){ 8, 9, 10, 11, ASCR_BACK, 0}},   //CharAnim_DownAlt
	{2, (const u8[]){ 12, 13, 14, 15, ASCR_BACK, 0}},         //CharAnim_Up
	{2, (const u8[]){ 12, 13, 14, 15, ASCR_BACK, 0}},   //CharAnim_UpAlt
	{2, (const u8[]){ 16, 17, 18, 19, ASCR_BACK, 0}},         //CharAnim_Right
	{2, (const u8[]){ 16, 17, 18, 19, ASCR_BACK, 0}},   //CharAnim_RightAlt
};
//cough character function
void Char_cough_SetFrame(void *user, u8 frame)
{
	Char_cough *this = (Char_cough*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_cough_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_cough_Tick(Character *character)
{
	Char_cough *this = (Char_cough*)character;
	
	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_cough_SetFrame);

	Character_Draw(character, &this->tex, &char_cough_frame[this->frame]);
}

void Char_cough_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_cough_Free(Character *character)
{
	Char_cough *this = (Char_cough*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_cough_New(fixed_t x, fixed_t y)
{
	//Allocate cough object
	Char_cough *this = Mem_Alloc(sizeof(Char_cough));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_cough_New] Failed to allocate cough object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_cough_Tick;
	this->character.set_anim = Char_cough_SetAnim;
	this->character.free = Char_cough_Free;
	
	Animatable_Init(&this->character.animatable, char_cough_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	this->character.health_i = 5;

	this->character.focus_x = FIXED_DEC(0,1);
	this->character.focus_y = FIXED_DEC(-65,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\COUGH.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle.tim", //cough_ArcMain_Idle1
		"left.tim",  //cough_ArcMain_Left
		"down.tim",  //cough_ArcMain_Down
		"up.tim",    //cough_ArcMain_Up
		"right.tim", //cough_ArcMain_Right
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
