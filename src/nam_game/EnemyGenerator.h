#pragma once
class EnemyGenerator :public GameObject
{
private:
	Score* m_score;
	Timer m_timeCreate;
	float m_timeReset;
	Mesh* m_meshEnemy;
public:
	EnemyGenerator();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	static Enemy* CreateEnemy(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, Mesh* mesh, Score* score);

	void SetParticleEmitter(GameObject* particleEmitter);
	GameObject* GetParticleEmitter();

	void SetMeshEnemy(Mesh* mesh);

	void SetScore(Score* score);
	void IncreaseGameScore(int add);
	Score* GetScore();
};

