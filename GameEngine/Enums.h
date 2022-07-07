#pragma once

enum class CollisionType
{
	// 2D�� 3D���� �浹�� �ȵǰ� ����̴ϴ�.
	Point2D,
	CirCle,
	Rect,
	OrientedRect,
	MAX,
};

enum class RenderingOrder
{
	BackBuffer, // ����ۿ� ���� �׸��°�
	World,
	UI,
	Debug,
};