#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineRandom.h>

class Flying_Cigar : public GameEngineActor
{
public:
	Flying_Cigar(); // default constructer ����Ʈ ������
	~Flying_Cigar(); // default destructer ����Ʈ �Ҹ���

private:		// delete constructer
	Flying_Cigar(const Flying_Cigar& _other) = delete; 
	Flying_Cigar(Flying_Cigar&& _other) = delete;
	Flying_Cigar& operator=(const Flying_Cigar& _other) = delete;
	Flying_Cigar& operator=(const Flying_Cigar&& _other) = delete;

private:
	class GameEngineCollision* Flying_CigarHitBox_;
	class GameEngineImageRenderer* Flying_CigarImageRenderer_;

	GameEngineImageRenderer* FireRenderer_;

	float TimeCheck_;
private:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
};

