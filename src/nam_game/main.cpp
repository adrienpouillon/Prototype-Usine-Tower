#include "pch.h"

enum Textures : size
{
	_Yellow,
	_Rainbow,
	_Stone,

	_Crepit,
	_Tuile,
	_Heart,
	_Grass,
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR cmdLine, int cmdShow)
{
    App* app = App::Get(hInstance, 1920, 1080);

	//start game
	{
		//system
		//app->AddSystem<...>();

		app->LoadTexture(L"yellow.dds", _Yellow, true);
		app->LoadTexture(L"rainbow.dds", _Rainbow, true);
		app->LoadTexture(L"stone.dds", _Stone, true);

		app->LoadTexture(L"crepit.dds", _Crepit, true);
		app->LoadTexture(L"tuile.dds", _Tuile, true);
		app->LoadTexture(L"heart.dds", _Heart, true);
		app->LoadTexture(L"grass.dds", _Grass, true);

		GameObject* appCamera = app->GetCamera();

		//creation caveScene
		Scene* caveScene = app->CreateScene(0);
		{
			//initialisation des objets
			Light* p_sun = app->GetLightManager().CreateLight();
			p_sun->SetToDirectionalLight(0.75f, { 0, -1, 0 }, { 1, 1, 1 });

			Player* player = caveScene->CreateGameObject<Player>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildBox({1,6,1}, {1.f,1.f,1.f,1.f});
				mesh->SetTexture(_Rainbow);


				XMFLOAT3 pos = XMFLOAT3(5.f, -20.f, 3.f);
				player->SetWorldPosition(pos);
				player->SetMesh(mesh);
			}

			GameObject* wall = caveScene->CreateGameObject<GameObject>();
			{
				BoxColliderComponent colli;
				wall->AddComponent(colli);
				wall->SetBoxCollider();
				wall->SetActiveEntity(true);

				Mesh* mesh = App::Get()->CreateEmptyMesh();
				mesh->BuildBox({ 50,2,2 }, { 0, 1, 0, 0 });
				mesh->MakeRainbowVertices();

				wall->SetTag((int)Tag::_Obstacle);
				wall->SetSphereCollider();
				wall->SetWorldPosition({ 0,-20,0 });
				wall->SetMesh(mesh);

			}
			player->SetWall(wall);
			Enemy* enemy = caveScene->CreateGameObject<Enemy>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildCylinder(0.5f, 20, 1.f,{ 1.f,1.f,1.f,1.f });
				mesh->SetTexture(_Rainbow);


				XMFLOAT3 pos = XMFLOAT3(0.f, -20.f, -20.f);
				enemy->SetWorldPosition(pos);
				enemy->SetMesh(mesh);
			}
			player->SetTarget(enemy);
			//creation floor
			GameObject* floor = caveScene->CreateGameObject<GameObject>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildPlane(XMFLOAT2(50.f, 50.f), { 1,1,1,1 }, true);
				mesh->SetTexture(_Grass);

				XMFLOAT3 pos = XMFLOAT3( 0.f, -20.f, 0.f);
				floor->SetWorldPosition(pos);
				floor->SetMesh(mesh);
			}

			//creation Camera
			Camera* camera = caveScene->CreateGameObject<Camera>();
			{
				camera->SetAppCamera(appCamera);
			}

			//button
			{
				GameObject* e1 = caveScene->CreateGameObject<GameObject>();

				DirectX::XMFLOAT3 pos = { 960, 540, 0 };
				DirectX::XMFLOAT3 ypr = { 0, 0, DirectX::XM_PIDIV4 };

				e1->SetWorldPosition(pos);
				e1->SetWorldYPR(ypr);

				ButtonComponent button;
				button.OnHovered = []() { std::cout << "hover" << std::endl; };
				button.OnClick = []() { std::cout << "click" << std::endl; };
				button.OnLeft = []() { std::cout << "left" << std::endl; };
				
				Sprite* sprite = app->CreateEmptySprite();
				sprite->BuildRect({200 ,100},{1,1,1,1});
				sprite->SetTexture(_Yellow);

				e1->AddComponent(sprite);
				e1->AddComponent(button);
			}

			//lancer
			caveScene->Start();
			app->AddCurrentScene(caveScene);
		}
	}

	//lancer le jeu
	app->Run();	
}