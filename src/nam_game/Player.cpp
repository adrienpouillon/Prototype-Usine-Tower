#include "pch.h"
#include "Player.h"

Player::Player()
{

}

void Player::OnInit()
{
	SetBehavior();
	SetTag((int)Tag::_Player);
}

void Player::OnStart()
{
	SetWorldPosition({ 0, 0, 0 });
}

void Player::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 scalePlayer = GetWorldScale();
	float speed = SPEED_PLAYER * dt;
	XMFLOAT3 posPlayer = GetWorldPosition();

	if (Input::IsKey('Z'))
	{
		MoveWorldForward(speed);
	}
	if (Input::IsKey('S'))
	{
		MoveWorldForward(-speed);
	}

	chrono.SetTimeWarp(1.f);

	if (Input::IsKey('A'))
	{
		chrono.SetTimeWarp(0.25f);
	}
	if (Input::IsKey('E'))
	{
		chrono.SetTimeWarp(4.f);
	}

	if (Input::IsKey(VK_SPACE))
	{
		XMFLOAT3 translation = { 0, speed, 0 };
		TranslateWorld(translation);
	}
	if (Input::IsKey(VK_LCONTROL))
	{
		XMFLOAT3 translation = { 0, -speed, 0 };
		TranslateWorld(translation);
	}

	/*GameObject* gameObjectParticleEmitter = GetParticleEmitter();
	ParticleEmitersComponent& particleEmiters = gameObjectParticleEmitter->GetComponent<ParticleEmitersComponent>();
	particleEmiters.m_maxXYZ[INDEX_PARTICLE_PlAYER] = XMFLOAT3(posPlayer.x + OFFSET_CENTER_PARTICLE, posPlayer.y + OFFSET_CENTER_PARTICLE, posPlayer.z + OFFSET_CENTER_PARTICLE);
	particleEmiters.m_minXYZ[INDEX_PARTICLE_PlAYER] = XMFLOAT3(posPlayer.x - OFFSET_CENTER_PARTICLE, posPlayer.y - OFFSET_CENTER_PARTICLE, posPlayer.z - OFFSET_CENTER_PARTICLE);*/
}

void Player::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{

}

void Player::OnDestroy()
{

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
