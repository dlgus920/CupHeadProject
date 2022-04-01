#pragma once

#define GV_GAMEFILENAME "CupHeadProject"

enum class CollisionGruop
{
	None,
	StagePoint,
	Player,
	PlayerHitBox,
	PlayerMoving,
	Bullet,
	UI
};

enum class ZOrder
{
	Z00Camera00,
	Z00Fx00,
	Z01Actor01,
	Z01Actor02,
	Z01Actor03,
	Z01Actor04,
	Z01Actor05,
	Z01Actor06,
	Z01Actor07,
	Z01Actor08,
	Z01Actor09,
	Z01Actor10,
	Z02Back01,
	Z02Back02,
	Z02Back03,
	Z02Back04,
	Z02Back05,
	Z02Back06,
	Z02Back07,
	Z02Back08,
	Z02Back09,
	Z02Back10,
	Z03Map00,
	Z04CollisonMap00,
	Z04CollisonMap01
};
