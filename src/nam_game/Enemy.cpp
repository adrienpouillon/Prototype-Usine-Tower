#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

void Enemy::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Player);
}

void Enemy::OnStart()
{

}

void Enemy::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 pos = XMFLOAT3(0.f * dt, 0.f * dt, 1.f * dt);
	TranslateWorld(pos);
}

void Enemy::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Enemy::OnDestroy()
{

}

void Enemy::SetScore(Score* score)
{
	m_score = score;
}

void Enemy::IncreaseGameScore(int add)
{
	m_score->IncreaseScore(add);
}

Score* Enemy::GetScore()
{
	return m_score;
}



