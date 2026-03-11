#pragma once
class Enemy : public GameObject
{
private:
	Score* m_score;
	int m_life;
public:
	Enemy();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetParticleEmitter(GameObject* particleEmitter);
	GameObject* GetParticleEmitter();

	void SetScore(Score* score);
	void IncreaseCreateMatter(int add);
	void IncreaseCropsZombie(int add);
	Score* GetScore();

	void SetLife(int life);
	int GetLife();
};

