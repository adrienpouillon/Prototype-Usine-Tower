#include "pch.h"
#include "Machine.h"

Machine::Machine()
{

}

void Machine::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Machine);
	m_multiply = 1.f;
}

void Machine::OnStart()
{

}

void Machine::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	if (Input::IsKey(VK_LBUTTON))
	{
		m_multiply += 0.1f;
	}

	if (Input::IsKey(VK_RBUTTON))
	{
		m_multiply -= 0.1f;
	}

	SetWorldScale(XMFLOAT3(1.f, ((int)m_multiply + 2) /10, 1.f));
}

void Machine::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Machine::OnDestroy()
{

}

void Machine::TimeUpdate()
{
	int cropsZombie = m_score->GetCropsZombie();
	if (cropsZombie > 0)
	{
		m_score->IncreaseCropsZombie(-1);
		m_score->IncreaseCreateMatter((int)m_multiply + 1);
	}

	if (m_multiply > 0.5f)
	{
		m_multiply -= 0.1f;
	}
	else
	{
		m_multiply = 0.1f;
	}
}

void Machine::SetScore(Score* score)
{
	m_score = score;
}

void Machine::IncreaseCreateMatter(int add)
{
	m_score->IncreaseCreateMatter(add);
}

void Machine::IncreaseCropsZombie(int add)
{
	m_score->IncreaseCropsZombie(add);
}

Score* Machine::GetScore()
{
	return m_score;
}

void Machine::IncreaseMultiply(float multiply)
{
	if (m_multiply > 0.5f)
	{
		m_multiply -= multiply;
	}
	else
	{
		m_multiply = 0.5f;
	}
}
