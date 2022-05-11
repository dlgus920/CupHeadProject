#pragma once

enum class CollisionGruop
{
	None,
	StagePoint,
	Player,
	PlayerParry,
	PlayerHitBox,
	PlayerMoving,
	Bullet,
	Parry,
	MonsterHitBox,
	MonsterAttack,
	UI
};

enum class ZOrder
{
	Z00Camera00,
	Z00Fx00,
	Z00Fx01,
	Z00Fx02,
	Z00UI,
	Z00PlayerFront00,
	Z00PlayerFront01,
	Z00PlayerFront02,
	Z00PlayerFront03,
	Z01Actor00Player01,
	Z01Actor01Bullet01,
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
	Z02Back11,
	Z02Back12,
	Z02Back13,
	Z02Back14,
	Z02Back15,
	Z03Map00,
	Z04CollisonMap00,
	Z04CollisonMap01
};
