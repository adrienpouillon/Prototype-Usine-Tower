#pragma once

class TimeReference : public GameObject
{
private:
	Timer m_timeUpdate;
	float m_timeReset;
	Machine* m_machine;
	Tower* m_tower;
	EnemyGenerator* m_enemyGenerator;
public:
	TimeReference();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetMachine(Machine* machine);
	void SetTower(Tower* tower);
	void SetEnemyGenerator(EnemyGenerator* enemyGenerator);

};

