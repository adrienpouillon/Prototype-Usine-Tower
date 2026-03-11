#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

void Enemy::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Enemy);
}

void Enemy::OnStart()
{

}

void Enemy::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 pos = XMFLOAT3(0.f * dt, 0.f * dt, 0.5f * dt);
	TranslateWorld(pos);
}

void Enemy::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObjectOther = App::Get()->GetGameObject(other);
	int tag = gameObjectOther->GetTag();
	if (tag == (int)Tag::_Shot || tag == (int)Tag::_Tower)
	{
		if (m_life > 0)
		{
			m_life--;
		}
		else
		{
			m_score->IncreaseCropsZombie(1);
			DestroyGameObject();
		}
	}
}

void Enemy::OnDestroy()
{

}

void Enemy::SetScore(Score* score)
{
	m_score = score;
}

void Enemy::IncreaseCreateMatter(int add)
{
	m_score->IncreaseCreateMatter(add);
}

void Enemy::IncreaseCropsZombie(int add)
{
	m_score->IncreaseCropsZombie(add);
}

Score* Enemy::GetScore()
{
	return m_score;
}

void Enemy::SetLife(int life)
{
	m_life = life;
}

int Enemy::GetLife()
{
	return m_life;
}



