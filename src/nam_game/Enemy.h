#pragma once
class Enemy : public GameObject
{
private:
	Score* m_score;
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
	void IncreaseGameScore(int add);
	Score* GetScore();
};

