#include "pch.h"
#include "Enemy.h"

Enemy::Enemy()
{
}

void Enemy::OnInit()
{
	SetBehavior();
	BoxColliderComponent colli;
	AddComponent(colli);
	SetBoxCollider();
	SetActiveEntity(true);
	SetTag((int)Tag::_Enemy);
}

void Enemy::OnStart()
{
}

void Enemy::OnUpdate()
{
	AppChrono& chrono = App::Get()->GetChrono();
	float dt = chrono.GetScaledDeltaTime();

	XMFLOAT3 scalePlayer = GetWorldScale();
	float speed = SPEED_PLAYER * dt;
	XMFLOAT3 posPlayer = GetWorldPosition();

	chrono.SetTimeWarp(1.f);

	XMFLOAT3 translation = { 0, 0, 3 * dt };
	TranslateWorld(translation);

}

void Enemy::OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo)
{
	GameObject* gameObject = App::Get()->GetGameObject(other);
	int tagOther = gameObject->GetTag();

	if (tagOther == (int)Tag::_Obstacle)
	{
		GameObject* wall = (GameObject*)gameObject;

		wall->DestroyGameObject();
		
	}
	if (tagOther == (int)Tag::_Shot)
	{
		GameObject* shot = (GameObject*)gameObject;

		shot->DestroyGameObject();
		DestroyGameObject();
	}
}

void Enemy::OnDestroy()
{

}
