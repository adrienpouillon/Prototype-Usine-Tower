#include "pch.h"
#include "TimeReference.h"

TimeReference::TimeReference()
{

}

void TimeReference::OnInit()
{
	m_timeReset = 0.5f;
	m_timeUpdate.SetTargetTime(m_timeReset);
}

void TimeReference::OnStart()
{

}

void TimeReference::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();
	m_timeUpdate.Update(dt);
	
	if (m_timeUpdate.IsTargetReached())
	{
		m_machine.
			m_tower
			m_enemyGenerator
	}
}

void TimeReference::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	
}

void TimeReference::OnDestroy()
{

}

void TimeReference::SetMachine(Machine* machine)
{
	m_machine = machine;
}

void TimeReference::SetTower(Tower* tower)
{
	m_tower = tower;
}

void TimeReference::SetEnemyGenerator(EnemyGenerator* enemyGenerator)
{
	m_enemyGenerator = enemyGenerator;
}

