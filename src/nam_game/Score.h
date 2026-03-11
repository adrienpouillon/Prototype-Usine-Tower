#pragma once

class Score : public GameObject
{
private:
	int m_createMatter;
	int m_cropsZombie;

	TextRendererComponent* mp_textRender;
public:
	Score();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	void SetCreateMatter(int createMatter);
	void IncreaseCreateMatter(int add);
	int GetCreateMatter();

	void SetCropsZombie(int cropsZombie);
	void IncreaseCropsZombie(int add);
	int GetCropsZombie();
};