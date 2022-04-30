#pragma once

enum OBJID { OBJ_FEATURE, OBJ_ITEM, OBJ_PLAYER, OBJ_BULLET, OBJ_MONSTER, OBJ_GUN, OBJ_MONSTER_BULLET, OBJ_MOUSE, OBJ_SHIELD, OBJ_BUTTON, OBJ_END };

enum SCENEID { SC_LOGO, SC_MENU, SC_EDIT, SC_STAGE, SC_END };

enum TEXTYPE { TEX_SINGLE, TEX_MULTI, TEX_END };

enum RENDERID { RENDER_BACKGROUND, RENDER_OBJ, RENDER_UI, RENDER_EFFECT, RENDER_END };

// 최대 32개 채널까지 동시 재생이 가능
enum CHANNELID { SOUND_EFFECT, SOUND_BGM, SOUND_PLAYER, SOUND_MONSTER, MAXCHANNEL };

enum MAPDATA_TYPE{DATA_NONE, DATA_INDESTRUCTIBLE_FEATRUE, DATA_DESTRUCTIBLE_FEATRUE, DATA_END};

enum class GUN_TYPE { PISTOL, AK47, SHOTGUN, RAILGUN, END };

enum class DIRECTION
{
	UP, DOWN, LEFT, RIGHT,
	UPLEFT, UPRIGHT,
	DOWNLEFT, DOWNRIGHT,
	NONE
};