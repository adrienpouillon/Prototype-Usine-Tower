#include "pch.h"
#include "Player.h"

Player::Player()
{

}

void Player::OnInit()
{
	m_afkTimer.Init(0.7f);

	SetBehavior();
	SetTag((int)Tag::_Player);
}

void Player::OnStart()
{
}

void Player::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
    float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 posPlayer = GetWorldPosition();

    // Mise à jour du timer de tir
    if (m_afkTimer.IsTargetReached())
    {
		if (mp_target && mp_wall != nullptr)
		{
			GameObject* shot = GetScene()->CreateGameObject<GameObject>();

			BoxColliderComponent colli;
			shot->AddComponent(colli);
			shot->SetBoxCollider();
			shot->SetActiveEntity(true);

			Mesh* mesh = App::Get()->CreateEmptyMesh();
			mesh->BuildBox({ 1,1,1 }, { 0, 0, 1, 0 });
			mesh->MakeRainbowVertices();

			shot->SetTag((int)Tag::_Shot);
			shot->SetSphereCollider();

			shot->SetWorldPosition({ posPlayer.x, posPlayer.y+ GetWorldScale().y*0.5f, posPlayer.z});
			shot->SetMesh(mesh);

			XMFLOAT3 t = mp_target->GetWorldPosition();
			shot->LookAtWorld(t);

			shots.push_back(shot);

			m_afkTimer.Init(0.7f);
		}
	}
	else
	{
		m_afkTimer.Update(dt);
	}

	if (mp_wall == nullptr)
	{
		shots.clear();
	}

	for (auto it = shots.begin(); it != shots.end(); )
	{
		GameObject* shot = *it;

		if (shot == nullptr || shot->GetScene() == nullptr)
		{
			it = shots.erase(it);
		}
		else
		{
			shot->MoveWorldForward(7 * dt);
			++it;
		}
	}
}

void Player::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Player::OnDestroy()
{
	shots.clear();
}

void Player::SetTarget(GameObject* p_target)
{
	mp_target = p_target;
}

void Player::SetWall(GameObject* p_Wall)
{
	mp_wall = p_Wall;
}

void Player::SetParticleEmitter(GameObject* particleEmitter)
{
	mp_particleEmitter = particleEmitter;
}

GameObject* Player::GetParticleEmitter()
{
	return mp_particleEmitter;
}

void Player::SetScore(Score* score)
{
	m_score = score;
}

void Player::IncreaseGameScore(int add)
{
	m_score->IncreaseScore(add);
}

Score* Player::GetScore()
{
	return m_score;
}
