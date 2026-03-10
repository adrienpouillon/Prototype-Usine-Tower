#include "pch.h"
#include "EnemyGenerator.h"
#include "Tower.h"

EnemyGenerator::EnemyGenerator()
{

}

void EnemyGenerator::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Player);
	m_timeReset = 2.f;
	m_timeCreate.SetTargetTime(m_timeReset);
}

void EnemyGenerator::OnStart()
{

}

void EnemyGenerator::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();
	m_timeCreate.Update(dt);

	if (m_timeCreate.IsTargetReached())
	{
		CreateEnemy(GetScene(), XMFLOAT3(5.f, 0.f, -10.f), XMFLOAT3(0.25f, 0.25f, 0.25f), m_meshEnemy, m_score);
		m_timeReset += Rng::Float(-0.2f, 0.1f);
		m_timeCreate.SetTargetTime(m_timeReset);
	}
}

void EnemyGenerator::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void EnemyGenerator::OnDestroy()
{

}

Enemy* EnemyGenerator::CreateEnemy(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, Mesh* mesh, Score* score)
{
	Enemy* enemy = scene->CreateGameObject<Enemy>();

	enemy->SetWorldPosition(pos);
	enemy->SetWorldScale(scale);
	enemy->SetMesh(mesh);
	enemy->SetScore(score);
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

void EnemyGenerator::IncreaseGameScore(int add)
{
	m_score->IncreaseScore(add);
}

Score* EnemyGenerator::GetScore()
{
	return m_score;
}
