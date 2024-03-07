#pragma once


enum OBJID{OBJ_WALL, OBJ_THORN,OBJ_GOAL,OBJ_MONSTER, OBJ_ATTACK,OBJ_SWORD, OBJ_PLAYER, OBJ_ITEM,OBJ_EFFECT,OBJ_HPBAR, OBJ_NUMBER,OBJ_HP, OBJ_END};

enum DIR{LEFT,RIGHT,UP,DOWN,NONE};

enum ITEMID{COIN , WEAPON};

enum SCENEID{SC_LOGO=0, SC_STAGE1,SC_STAGE2,SC_STAGE3,SC_STAGE4,SC_END};

enum CHANNELID { SOUND_PLAYER_WALK,SOUND_PLAYER_JUMP,SOUND_PLAYER_FALL,SOUND_PLAYER_LAND,SOUND_PLAYER_HEALING,SOUND_PLAYER_DASH,SOUND_PLAYER_DAMAGED,
	SOUND_SWORD_EFFECT1,
	 SOUND_BGM, SOUND_MONSTER_ATTACKED,SOUND_MONSTER_DEAD,SOUND_MONSTER_FLY,
	SOUND_SEMIBOSS_SOUND1,SOUND_SEMIBOSS_SOUND2,SOUND_SEMIBOSS_ATTACK,SOUND_SEMIBOSS,SOUND_SEMIBOSS_JUMP,SOUND_SEMIBOSS_SOUND3,
	SOUND_WIND,
	THORN1,

	MAXCHANNEL };