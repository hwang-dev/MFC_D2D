#pragma once

enum TEXTYPE { 
	TEX_SINGLE, 
	TEX_MULTI, 
	TEX_END 
};

enum OBJID { 
	OBJ_TERRAIN, 
	OBJ_PLAYER, 
	OBJ_MONSTER,
	OBJ_BULLET,
	OBJ_END 
};

enum PLAYER_STANCE {
	IDLE, 
	MOVE, 
	DODGE, 
	STANCE_END
};

enum PLAYER_DIR {
	UP, 
	DOWN, 
	LEFT, 
	RIGHT,
	UP_LEFT, 
	UP_RIGHT, 
	DOWN_LEFT, 
	DOWN_RIGHT,
	DIR_END
};

enum MONSTER_TYPE {
	REVOLVER,
	SHOTGUN,
	MAGIC,
	TYPE_END
};

