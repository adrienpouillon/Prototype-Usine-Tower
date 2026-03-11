#pragma once
class Shot : public GameObject
{
private:
	XMFLOAT3 m_velocity;
	Timer m_timeDestroy;
public:
	Shot();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetVelocity(XMFLOAT3 velocity);
	XMFLOAT3 GetVelocity();
};

