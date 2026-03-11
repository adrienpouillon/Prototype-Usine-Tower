#include "pch.h"
#include "Shot.h"

Shot::Shot()
{

}

void Shot::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Shot);
	m_timeDestroy.SetTargetTime(50.f);
}

void Shot::OnStart()
{

}

void Shot::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	m_timeDestroy.Update(dt);
	TranslateWorld(XMFLOAT3(m_velocity.x * dt, m_velocity.y * dt, m_velocity.z * dt));

	if (m_timeDestroy.IsTargetReached())
	{
		DestroyGameObject();
		m_timeDestroy.ResetProgress();
	}
}

void Shot::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObjectOther = App::Get()->GetGameObject(other);
	int tag = gameObjectOther->GetTag();
	if (tag == (int)Tag::_Enemy || tag == (int)Tag::_EnemyGenerator)
	{
		DestroyGameObject();
	}
}

void Shot::OnDestroy()
{

}

void Shot::SetVelocity(XMFLOAT3 velocity)
{
	m_velocity = velocity;
}

XMFLOAT3 Shot::GetVelocity()
{
	return m_velocity;
}
