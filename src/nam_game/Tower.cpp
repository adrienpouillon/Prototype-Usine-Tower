#include "pch.h"
#include "Tower.h"

Tower::Tower()
{

}

void Tower::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Tower);
	m_timeReset = 0.5f;
	m_timeCreate.SetTargetTime(m_timeReset);
	m_life = 10;
}

void Tower::OnStart()
{

}

void Tower::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	SetWorldScale(XMFLOAT3(m_timeReset + 1.f, 1.f, (float)m_life/5.f + 0.1f));
}

void Tower::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObjectOther = App::Get()->GetGameObject(other);
	int tag = gameObjectOther->GetTag();
	if (tag == (int)Tag::_Enemy)
	{
		m_life--;
	}
}

void Tower::OnDestroy()
{
	
}

void Tower::TimeUpdate()
{
	int createMatter = m_score->GetCreateMatter();
	if (createMatter > 0)
	{
		m_score->SetCreateMatter(createMatter - 1);
		CreateShot(GetScene(), GetWorldPosition(), XMFLOAT3(0.1f, 0.1f, 0.1f), XMFLOAT3(0.f, 0.f, -1.f), m_meshShot);
		m_timeReset += Rng::Float(-0.04f, 0.02f);
	}
}

Shot* Tower::CreateShot(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 velocity, Mesh* mesh)
{
	Shot* shot = scene->CreateGameObject<Shot>();
	shot->SetWorldPosition(pos);
	shot->SetWorldScale(scale);
	shot->SetVelocity(velocity);
	shot->SetMesh(mesh);
	shot->SetSphereCollider();
	return shot;
}

void Tower::SetMeshShot(Mesh* mesh)
{
	m_meshShot = mesh;
}

void Tower::SetScore(Score* score)
{
	m_score = score;
}

void Tower::IncreaseCreateMatter(int add)
{
	m_score->IncreaseCreateMatter(add);
}

void Tower::IncreaseCropsZombie(int add)
{
	m_score->IncreaseCropsZombie(add);
}

Score* Tower::GetScore()
{
	return m_score;
}

void Tower::IncreaseTimeReset(float timeReset)
{
	m_timeReset += timeReset;
}
