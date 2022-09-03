#include "PreCompile.h"
#include "GameEngineCollision.h"
#include "GameEngineLevel.h"
#include "GameEngineTransform.h"


std::function<bool(GameEngineTransform*, GameEngineTransform*)>
GameEngineCollision::CollisionCheckFunction[static_cast<int>(CollisionType::MAX)][static_cast<int>(CollisionType::MAX)];


void GameEngineCollision::Init() 
{
	CollisionCheckFunction[static_cast<int>(CollisionType::CirCle)][static_cast<int>(CollisionType::CirCle)]
		= std::bind(&GameEngineCollision::CirCleToCirCle, std::placeholders::_1, std::placeholders::_2);

	CollisionCheckFunction[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::Rect)]
		= std::bind(&GameEngineCollision::RectToRect, std::placeholders::_1, std::placeholders::_2);

	CollisionCheckFunction[static_cast<int>(CollisionType::Rect)][static_cast<int>(CollisionType::CirCle)]
		= std::bind(&GameEngineCollision::RectToCirCle, std::placeholders::_1, std::placeholders::_2);

	CollisionCheckFunction[static_cast<int>(CollisionType::CirCle)][static_cast<int>(CollisionType::Rect)]
		= std::bind(&GameEngineCollision::CirCleToRect, std::placeholders::_1, std::placeholders::_2);


}

bool GameEngineCollision::RectToRect(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingOrientedBox Left = _Left->GetOBB();
	DirectX::BoundingOrientedBox Right = _Right->GetOBB();
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;
	return Left.Intersects(Right);
}

bool GameEngineCollision::CirCleToCirCle(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingSphere Left = _Left->GetSphere();
	DirectX::BoundingSphere Right = _Right->GetSphere();
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;
	return Left.Intersects(Right);
}

bool GameEngineCollision::RectToCirCle(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	DirectX::BoundingOrientedBox Left = _Left->GetOBB();
	DirectX::BoundingSphere Right = _Right->GetSphere();
	Left.Center.z = 0.0f;
	Right.Center.z = 0.0f;
	return Left.Intersects(Right);
}

bool GameEngineCollision::CirCleToRect(GameEngineTransform* _Left, GameEngineTransform* _Right)
{
	RectToCirCle(_Right, _Left);
	return false;
}

//bool GameEngineCollision::OBBToOBB(GameEngineTransform* _Left, GameEngineTransform* _Right) {
//	return _Left->GetOBB().Intersects(_Right->GetOBB());
//}
// 
//bool GameEngineCollision::AABBToAABB(GameEngineTransform* _Left, GameEngineTransform* _Right)
//{
//	return _Left->GetAABB().Intersects(_Right->GetAABB());
//}

//bool GameEngineCollision::Sphere3DToSphere3D(GameEngineTransform* _Left, GameEngineTransform* _Right)
//{
//	return _Left->GetSphere().Intersects(_Right->GetSphere());
//}

GameEngineCollision::GameEngineCollision() 
{
}

GameEngineCollision::~GameEngineCollision() 
{
}

void GameEngineCollision::Start()
{
	GetLevel()->PushCollision(this, GetOrder());
}

void GameEngineCollision::Update(float _DeltaTime)
{
}

void GameEngineCollision::SetCollisionGroup(int _Type)
{
	GetLevel()->ChangeCollisionGroup(_Type, this);
}

//void GameEngineCollision::Collision(CollisionType _ThisType, CollisionType _OtherType, int _OtherGroup, std::function<void(GameEngineCollision*)> _CallBack)
//{
//	std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);
//
//	for (GameEngineCollision* OtherCollision : Group)
//	{
//		if (false == OtherCollision->IsUpdate())
//		{
//			continue;
//		}
//
//		auto& CheckFunction = CollisionCheckFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)];
//#ifdef _DEBUG
//		if (nullptr == CheckFunction)
//		{
//			GameEngineDebug::MsgBoxError("아직 구현하지 않는 타입간에 충돌을 하려고 했습니다.");
//		}
//#endif // _DEBUG
//
//		if (
//			false == 
//			CheckFunction(GetTransform(), OtherCollision->GetTransform())
//			)
//		{
//			continue;
//		}
//
//		_CallBack(OtherCollision);
//	}
//}

bool GameEngineCollision::Collision(int _OtherGroup)
{
	if (GetIsUpdateRef())
	{
		std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

		for (GameEngineCollision* OtherCollision : Group)
		{
			if (false == OtherCollision->IsUpdate())
			{
				continue;
			}

			auto& CheckFunction = CollisionCheckFunction[static_cast<int>(CollisionType_)]
				[static_cast<int>(OtherCollision->CollisionType_)];
#ifdef _DEBUG
			if (nullptr == CheckFunction)
			{
				GameEngineDebug::MsgBoxError("아직 구현하지 않는 타입간에 충돌을 하려고 했습니다.");
			}
#endif // _DEBUG

			if (false == CheckFunction(GetTransform(), OtherCollision->GetTransform()))
			{
				continue;
			}

			return true;
		}
		return false;
	}
	return false;
}

GameEngineCollision* GameEngineCollision::CollisionPtr(int _OtherGroup)
{
	if (true == IsUpdate())
	{
		GameEngineCollision* RetCollision = nullptr;
		float retdist = 0.f;
		float comparedist = 0.f;

		std::list<GameEngineCollision*>& Group = GetLevel()->GetCollisionGroup(_OtherGroup);

		for (GameEngineCollision* OtherCollision : Group)
		{
			if (false == OtherCollision->IsUpdate())
			{
				continue;
			}

#ifdef _DEBUG
			//auto& CheckFunction = CollisionCheckFunction[static_cast<int>(CollisionType_)]
				//[static_cast<int>(OtherCollision->CollisionType_)];
				// 
			//if (nullptr == CheckFunction)
			if (nullptr == CollisionCheckFunction[static_cast<int>(CollisionType_)]
				[static_cast<int>(OtherCollision->CollisionType_)])
			{
				GameEngineDebug::MsgBoxError("아직 구현하지 않는 타입간에 충돌을 하려고 했습니다.");
			}
#endif // _DEBUG

			if (false == CollisionCheckFunction[static_cast<int>(CollisionType_)]
				[static_cast<int>(OtherCollision->CollisionType_)](GetTransform(), OtherCollision->GetTransform()))
			{
				continue;
			}

			float4 cal = GetTransform()->GetWorldPosition() - OtherCollision->GetTransform()->GetWorldPosition();

			comparedist = cal.Len3D();

			if (retdist == 0.f)
			{
				retdist = comparedist;
				RetCollision = OtherCollision;
			}

			else if (comparedist > retdist)
			{
				continue;
			}
			else
			{
				retdist = comparedist;
				RetCollision = OtherCollision;
			}

   		}
		return RetCollision;
	}

	return nullptr;
}