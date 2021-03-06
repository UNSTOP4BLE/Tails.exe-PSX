	{ //StageId_1_1 (Bopeebo)
		//Characters
		{Char_BF_New,    FIXED_DEC(60 + 90,1),  FIXED_DEC(100,1)},
		{Char_Dad_New, FIXED_DEC(-120 + 130,1),  FIXED_DEC(100,1)},
		{NULL},
		{Char_GF_New,     FIXED_DEC(0 + 90,1),  FIXED_DEC(-10,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(28,10),FIXED_DEC(1,1)},
		1, 1,
		XA_Bopeebo, 0,
		
		StageId_1_2, STAGE_LOAD_STAGE
	},
	{ //StageId_1_2 (Fresh)
		//Characters
		{Char_BF_New,    FIXED_DEC(60 + 90,1),  FIXED_DEC(100,1)},
		{Char_Dad_New, FIXED_DEC(-120 + 130,1),  FIXED_DEC(100,1)},
		{NULL},
		{Char_GF_New,     FIXED_DEC(0 + 90,1),  FIXED_DEC(-10,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(28,10),FIXED_DEC(1,1)},
		1, 2,
		XA_Fresh, 2,
		
		StageId_1_3, STAGE_LOAD_STAGE | STAGE_LOAD_OPPONENT | STAGE_LOAD_OPPONENT2 | STAGE_LOAD_PLAYER | STAGE_LOAD_GIRLFRIEND
	},
	{ //StageId_1_3 (Dadbattle)
		//Characters
		{Char_bfb_New,    FIXED_DEC(60 + 90,1),  FIXED_DEC(100,1)},
		{Char_spook_New, FIXED_DEC(-120 + 160,1),  FIXED_DEC(100,1)},
		{Char_tailsd_New, FIXED_DEC(-120 + 90,1),  FIXED_DEC(100,1)},
		{Char_gfb_New,     FIXED_DEC(0 + 90,1),  FIXED_DEC(-10,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(28,10),FIXED_DEC(1,1)},
		1, 3,
		XA_Dadbattle, 0,
		
		StageId_1_3, 0
	},
	{ //StageId_1_4 (Tutorial)
		//Characters
		{Char_BF_New, FIXED_DEC(90,1),  FIXED_DEC(100,1)},
		{Char_cough_New,  FIXED_DEC(-10,1),  FIXED_DEC(80,1)},
		{NULL},
		{NULL},
		
		//Stage background
		Back_Dummy_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(28,10),FIXED_DEC(1,1)},
		1, 4,
		XA_Tutorial, 2,
		
		StageId_1_4, 0
	},
