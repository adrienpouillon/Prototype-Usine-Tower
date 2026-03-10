#include "pch.h"
#include "Tower.h"

Tower::Tower()
{

}

void Tower::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Player);
	m_timeCreate.SetTargetTime(2.f);
}

void Tower::OnStart()
{

}

void Tower::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();
	
	m_timeCreate.Update(dt);

	if (m_timeCreate.IsTargetReached())
	{
		CreateEnemy(GetScene(), XMFLOAT3(5.f, 0.f, -10.f), XMFLOAT3(0.25f, 0.25f, 0.25f), m_meshShot);
		m_timeCreate.ResetProgress();
	}
}

void Tower::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Tower::OnDestroy()
{

}

Enemy* Tower::CreateEnemy(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, Mesh* mesh, Score* score)
{
	Enemy* enemy = scene->CreateGameObject<Enemy>();

	enemy->SetWorldPosition(pos);
	enemy->SetWorldScale(scale);
	enemy->SetMesh(mesh);
	enemy->SetScore(score);
	return enemy;
}

void Tower::SetMeshEnemy(Mesh* mesh)
{
	m_meshEnemy = mesh;
}