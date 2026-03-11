#include "pch.h"
#include "Score.h"

Score::Score()
{
	m_createMatter = 0;
	m_cropsZombie = 0;
}

void Score::OnInit()
{
	m_createMatter = 10;
	m_cropsZombie = 0;

	TextRendererComponent textRender;

	Text* p_text = textRender.CreateTextInstance();

	p_text->SetDatas({ 40, 40 }, 0.5f, { 1, 1, 1, 1 });
	p_text->SetText("Score : ");

	p_text->SetTexture(_FontPusab);
	p_text->SetToDynamic(MAX_TEXT_VERTICES, MAX_TEXT_INDICES);

	XMFLOAT3 pos = { 20, 20, 0 };
	SetWorldPosition(pos);
	AddComponent(textRender);
	mp_textRender = &GetComponent<TextRendererComponent>();

	SetBehavior();
	SetTag((int)Tag::_None);
}

void Score::OnStart()
{

}

void Score::OnUpdate()
{
	App* app = App::Get();
	float dt = app->GetChrono().GetScaledDeltaTime();

	std::string toDisplay = "Matiere Creatrice : " + std::to_string(m_createMatter) + "\n" + "Cadavre Zombie : " + std::to_string(m_cropsZombie);
	mp_textRender->mp_text->SetText(toDisplay);
	mp_textRender->mp_text->MakeRainbowVertices();
}

void Score::OnDestroy()
{

}

void Score::SetCreateMatter(int createMatter)
{
	m_createMatter = createMatter;
}

void Score::IncreaseCreateMatter(int add)
{
	m_createMatter += add;
}

int Score::GetCreateMatter()
{
	return m_createMatter;
}

void Score::SetCropsZombie(int cropsZombie)
{
	m_cropsZombie = cropsZombie;
}

void Score::IncreaseCropsZombie(int add)
{
	m_cropsZombie += add;
}

int Score::GetCropsZombie()
{
	return m_cropsZombie;
}


