#include "pch.h"
#include "Machine.h"

Machine::Machine()
{

}

void Machine::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Machine);
	m_timeTrans.SetTargetTime(0.5f);
	m_multiply = 1.f;
}

void Machine::OnStart()
{

}

void Machine::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();
	m_timeTrans.Update(dt);

	if (Input::IsKey(VK_LBUTTON))
	{
		m_multiply += 0.1f;
	}

	if (Input::IsKey(VK_RBUTTON))
	{
		m_multiply -= 0.1f;
	}

	int matterAdd = (int)m_multiply + 1;
	SetWorldScale(XMFLOAT3(1.f, (m_multiply + 1) /10, 1.f));

	if (m_timeTrans.IsTargetReached())
	{
		int cropsZombie = m_score->GetCropsZombie();
		if (cropsZombie > 0)
		{
			m_score->IncreaseCropsZombie(-1);
			m_score->IncreaseCreateMatter(matterAdd);
			m_timeTrans.ResetProgress();
		}
	}
	if(m_multiply>0.5f)
	{
		m_multiply -= 0.01f;
	}
	else
	{
		m_multiply = 0.5f;
	}
}

void Machine::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Machine::OnDestroy()
{

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
