#include "pch.h"
#include "EnemyGenerator.h"

EnemyGenerator::EnemyGenerator()
{

}

void EnemyGenerator::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_EnemyGenerator);
	m_timeReset = 4.f;
	m_timeCreate.SetTargetTime(m_timeReset);
	m_lifeZombie = 3.f;
	m_life = 10;
}

void EnemyGenerator::OnStart()
{

}

void EnemyGenerator::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();
	m_timeCreate.Update(dt);

	SetWorldScale(XMFLOAT3(m_timeReset + 1.f, (float)m_lifeZombie/10.f, (float)m_life/5 + 0.1f));

	if (m_timeCreate.IsTargetReached())
	{
		CreateEnemy(GetScene(), GetWorldPosition(), XMFLOAT3(0.25f, 0.25f, 0.25f), m_meshEnemy, m_score, m_lifeZombie);
		if(Rng::Int(0, 2) == 1)
		{
			m_lifeZombie += Rng::Int(-1, 2);
			m_timeReset += Rng::Float(-0.2f, 0.1f);
			m_timeReset += Rng::Float(-0.2f, 0.1f);

			if (m_lifeZombie < 1)
			{
				m_lifeZombie = 1;
			}
		}
		m_timeCreate.SetTargetTime(m_timeReset);
	}
}

void EnemyGenerator::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObjectOther = App::Get()->GetGameObject(other);
	int tag = gameObjectOther->GetTag();
	if (tag == (int)Tag::_Shot)
	{
		m_life--;
	}
}

void EnemyGenerator::OnDestroy()
{

}

Enemy* EnemyGenerator::CreateEnemy(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, Mesh* mesh, Score* score, int life)
{
	Enemy* enemy = scene->CreateGameObject<Enemy>();
	enemy->SetWorldPosition(pos);
	enemy->SetWorldScale(scale);
	enemy->SetMesh(mesh);
	enemy->SetScore(score);
	enemy->SetSphereCollider();
	enemy->SetLife(life);
	return enemy;
}

void EnemyGenerator::SetMeshEnemy(Mesh* mesh)
{
	m_meshEnemy = mesh;
}

void EnemyGenerator::SetScore(Score* score)
{
	m_score = score;
}

void EnemyGenerator::IncreaseCreateMatter(int add)
{
	m_score->IncreaseCreateMatter(add);
}

void EnemyGenerator::IncreaseCropsZombie(int add)
{
	m_score->IncreaseCropsZombie(add);
}

Score* EnemyGenerator::GetScore()
{
	return m_score;
}
