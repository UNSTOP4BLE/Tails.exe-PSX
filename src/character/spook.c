/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "spook.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//spook character structure
enum
{
	spook_ArcMain_Idle0,
	spook_ArcMain_Idle1,
	spook_ArcMain_Idle2,
	spook_ArcMain_Idle3,
	spook_ArcMain_Left0,
	spook_ArcMain_Left1,
	spook_ArcMain_Down0,
	spook_ArcMain_Down1,
	spook_ArcMain_Up0,
	spook_ArcMain_Up1,
	spook_ArcMain_Right0,
	spook_ArcMain_Right1,
	
	spook_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[spook_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_spook;

//spook character definitions
static const CharFrame char_spook_frame[] = {
	{spook_ArcMain_Idle0, {  0,   0, 134, 228}, { 134, 228}},  //0 idle 1
	{spook_ArcMain_Idle1, {  0,   0, 133, 228}, { 133, 228}},  //1 idle 2
	{spook_ArcMain_Idle2, {  0,   0, 135, 230}, { 135, 230}},  //2 idle 3
	{spook_ArcMain_Idle3, {  0,   0, 134, 235}, { 134, 235}},  //3 idle 4
	
	{spook_ArcMain_Left0, {  0,   0, 215, 213}, { 181, 213}},  //4 left 1
	{spook_ArcMain_Left1, {  0,   0, 211, 213}, { 174, 213}},  //5 left 2

	{spook_ArcMain_Down0, {  0,   0, 153, 199}, { 145, 199}},  //6 down 1
	{spook_ArcMain_Down1, {  0,   0, 153, 209}, { 144, 209}},  //7 down 2
	
	{spook_ArcMain_Up0, {  0,   0, 156, 255}, { 145, 255}},  //8 up 1
	{spook_ArcMain_Up1, {  0,   0, 155, 239}, { 147, 239}},  //9 up 2
	
	{spook_ArcMain_Right0, {  0,   0, 188, 218}, { 58, 218}},  //10 right 1
	{spook_ArcMain_Right1, {  0,   0, 183, 218}, { 59, 218}},  //11 right 2
};

static const Animation char_spook_anim[CharAnim_Max] = {
	{2, (const u8[]){ 0, 1, 2, 3, ASCR_BACK, 0}}, //CharAnim_Idle
	{2, (const u8[]){ 4, 5, ASCR_BACK, 0}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 6, 7, ASCR_BACK, 0}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{2, (const u8[]){ 8, 9, ASCR_BACK, 0}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{2, (const u8[]){ 10, 11, ASCR_BACK, 0}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//spook character functions
void Char_spook_SetFrame(void *user, u8 frame)
{
	Char_spook *this = (Char_spook*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_spook_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_spook_Tick(Character *character)
{
	Char_spook *this = (Char_spook*)character;

	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	 Animatable_Animate(&character->animatable, (void*)this, Char_spook_SetFrame);

	Character_Draw(character, &this->tex, &char_spook_frame[this->frame]);
}

void Char_spook_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_spook_Free(Character *character)
{
	Char_spook *this = (Char_spook*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_spook_New(fixed_t x, fixed_t y)
{
	//Allocate spook object
	Char_spook *this = Mem_Alloc(sizeof(Char_spook));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_spook_New] Failed to allocate spook object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_spook_Tick;
	this->character.set_anim = Char_spook_SetAnim;
	this->character.free = Char_spook_Free;
	
	Animatable_Init(&this->character.animatable, char_spook_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	this->character.health_i = 1;

	this->character.focus_x = FIXED_DEC(55,1);
	this->character.focus_y = FIXED_DEC(-75,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\SPOOK.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //spook_ArcMain_Idle0
		"idle1.tim", //spook_ArcMain_Idle1
		"idle2.tim", //spook_ArcMain_Idle1
		"idle3.tim", //spook_ArcMain_Idle1
		"left0.tim",  //spook_ArcMain_Left
		"left1.tim",  //spook_ArcMain_Left
		"down0.tim",  //spook_ArcMain_Down
		"down1.tim",  //spook_ArcMain_Down
		"up0.tim",    //spook_ArcMain_Up
		"up1.tim",    //spook_ArcMain_Up
		"right0.tim", //spook_ArcMain_Right
		"right1.tim", //spook_ArcMain_Right
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
