#pragma once
class Tower : public GameObject
{
private:
	Score* m_score;
	Mesh* m_meshShot;
	Timer m_timeCreate;
	float m_timeReset;
	int m_life;
public:
	Tower();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	static Shot* CreateShot(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 velocity, Mesh* mesh);

	void SetMeshShot(Mesh* mesh);

	void SetScore(Score* score);
	void IncreaseCreateMatter(int add);
	void IncreaseCropsZombie(int add);
	Score* GetScore();
};

