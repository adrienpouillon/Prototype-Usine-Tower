#pragma once
class Machine : public GameObject
{
private:
	Score* m_score;
	Timer m_timeTrans;
	float m_multiply;
public:
	Machine();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	void SetScore(Score* score);
	void IncreaseCreateMatter(int add);
	void IncreaseCropsZombie(int add);
	Score* GetScore();

	void IncreaseMultiply(float multiply);
};

