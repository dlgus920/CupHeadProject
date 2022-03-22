#pragma once

enum class CollisionGruop
{
	None,
	Player,
	PlayerHitBox,
	PlayerMoving,
	Bullet,
	UI
};

enum class RenderOrder
{
	Back,
	Actor,
	Player,
	Bullet
};