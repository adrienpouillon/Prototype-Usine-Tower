#pragma once
class Tower : public GameObject
{
private:
	Mesh* m_meshShot;
	Timer m_timeCreate;
public:
	Tower();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnCollision(u32 self, u32 other, const CollisionInfo& collisionInfo) override;
	void OnDestroy() override;

	static Enemy* CreateEnemy(Scene* scene, XMFLOAT3 pos, XMFLOAT3 scale, Mesh* mesh, Score* score);

	void SetMeshEnemy(Mesh* mesh);
};

