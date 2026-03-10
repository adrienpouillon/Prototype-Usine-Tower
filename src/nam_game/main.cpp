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

			//creation player
			Player* player = caveScene->CreateGameObject<Player>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildCylinder(0.5f, 20, 1.f, { 1.f,1.f,1.f,1.f });
				mesh->SetTexture(_Stone);


				XMFLOAT3 pos = XMFLOAT3(0.f, 1.f, -5.f);
				player->SetWorldPosition(pos);
				player->SetMesh(mesh);
			}

			//creation enemy
			GameObject* enemy = caveScene->CreateGameObject<GameObject>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildUvSphere(1.f, 20, 20, { 1, 1, 1, 1 });
				mesh->MakeRainbowVertices();
				mesh->SetTexture(_Stone);

				XMFLOAT3 pos = XMFLOAT3( -1.f, 1.f, 5.f);

				enemy->SetSphereCollider();
				enemy->SetWorldPosition(pos);
				enemy->SetMesh(mesh);
			}		

			//creation floor
			GameObject* floor = caveScene->CreateGameObject<GameObject>();
			{
				Mesh* mesh = app->CreateEmptyMesh();
				mesh->BuildPlane(XMFLOAT2(50.f, 50.f), { 1,1,1,1 }, true);
				mesh->SetTexture(_Grass);

				XMFLOAT3 pos = XMFLOAT3( 0.f, -5.f, 10.f);
				floor->SetWorldPosition(pos);
				floor->SetMesh(mesh);
			}

			//creation Camera
			Camera* camera = caveScene->CreateGameObject<Camera>();
			{
				camera->SetAppCamera(appCamera);
				camera->SetTarget(player);
			}

			//creation Particle Emitter
			GameObject* particleEmitter = caveScene->CreateGameObject<GameObject>();
			{
				TransformComponent transform;
				DirectX::XMFLOAT3 pos = { 0, 1, 4 };
				transform.SetWorldPosition(pos);

				ParticleEmitersComponent emiters;
				{
					XMFLOAT3 maxXYZ = { 0,2,0 }; XMFLOAT3 minXYZ = { 0,2,0 }; XMFLOAT3 maxDir = { 1,1,1 }; XMFLOAT3 minDir = { -1,-1,-1 }; XMFLOAT3 startColor = { 1,0,0 }; XMFLOAT3 endColor = { 1,1,0 }; float maxSpeed = 0.5f; float minSpeed = 0.3f; float lifeTime = 2.f; float spawnRate = 100.f;
					emiters.AddEmiter(maxXYZ, minXYZ, maxDir, minDir, startColor, endColor, maxSpeed, minSpeed, lifeTime, spawnRate);
				}

				{
					XMFLOAT3 maxXYZ = { 0,3,0 }; XMFLOAT3 minXYZ = { 0,3,0 }; XMFLOAT3 maxDir = { 1,1,1 }; XMFLOAT3 minDir = { -1,-1,-1 }; XMFLOAT3 startColor = { 0,1,0 }; XMFLOAT3 endColor = { 0,1,1 }; float maxSpeed = 0.5f; float minSpeed = 0.3f; float lifeTime = 2.f; float spawnRate = 100.f;
					emiters.AddEmiter(maxXYZ, minXYZ, maxDir, minDir, startColor, endColor, maxSpeed, minSpeed, lifeTime, spawnRate);
				}

				{
					XMFLOAT3 maxXYZ = { 0,1,0 }; XMFLOAT3 minXYZ = { 0,1,0 }; XMFLOAT3 maxDir = { 1,1,1 }; XMFLOAT3 minDir = { -1,-1,-1 }; XMFLOAT3 startColor = { 0,0,1 }; XMFLOAT3 endColor = { 1,0,1 }; float maxSpeed = 0.5f; float minSpeed = 0.3f; float lifeTime = 2.f; float spawnRate = 100.f;
					emiters.AddEmiter(maxXYZ, minXYZ, maxDir, minDir, startColor, endColor, maxSpeed, minSpeed, lifeTime, spawnRate);
				}

				particleEmitter->AddComponent(transform);
				particleEmitter->AddComponent(emiters);
			}

			//creation score
			Score* score = caveScene->CreateGameObject<Score>();
			{
				//score->AddComponent<>
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