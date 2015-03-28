#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>
#include <InputManager.h>
#include <sstream> 
#include <string.h>
#include "MessageUtils.h"
#include "SoundHelper.h"

#include "Enemy.h"
#include "Player.h"
#include "Cube.h"
#include <Cameras/Camera.h>
#include <Cameras/PerspectiveCamera.h>
#include <Cameras/OrthographicCamera.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;
Player* player;
Enemy* enemies[MAX_ENEMIES] = { 0 }; // array of enemies

float lastEnemySpawnTime = 0; // time that the last enemy was borned

int visitedFloors = 0; // number of tiles that the player visited
int floors = 5; // mumber of "lines" in the pyramide of cubes

int currentLevel = 1;




GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{

}


void Game::CreateFloors()
{

	float x = 0;
	float y = 2;
	float z = 0;


	_objects.push_back(new Cube(Vector3(x, y, z)));

	for (int floor = 2; floor <= floors; floor++)
	{
		y--;
		for (int tile = 1; tile <= floor; tile++)
		{
			float tileX = 0, tileY = 0, tileZ = 0.0f;
			tileY = y;

			if (tile == 1)
			{
				tileX = x + (floor - 1);
				tileZ = z;
			}
			else if (tile == floor)
			{
				tileX = x;
				tileZ = z + (floor - 1);
			}
			else
			{
				tileX = (tile - 1);
				tileZ = floor - tile;
			}
			_objects.push_back(new Cube(Vector3(tileX, tileY, tileZ)));
		}
	}
}
void Game::InitializeImpl()
{
	_soundHelper = new SoundHelper();
	_soundHelper->Initialize();

	_windowTitle = new char[25];
	strcpy(_windowTitle, "My QBert - Life: 3 | Level: 1	");
	SDL_SetWindowTitle(_window, _windowTitle);

	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	Vector4 position(3.5f, 3.0f, 4.5f, 0.0f);
	Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
	Vector4 up(0.0f, 2.0f, 0.0f, 0.0f);

	_camera = new PerspectiveCamera(100.0f, 1.0f, nearPlane, farPlane, position, lookAt, up);
	//_camera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);


	CreateFloors();

	player = new Player(Vector3(startX, startY + CHAR_HEIGHT, startZ));
	_objects.push_back(player);

	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{
		(*itr)->Initialize(_graphicsObject);
	}

}

int Game::GetPathIndex(Vector3 position, Direction direction)
{
	int index = 0;
	float x = 0, y = 0, z = 0;

	if (direction == LEFT)
	{
		//	y = 1;
		x = -1;
	}
	else if (direction == RIGHT)
	{
		x = 1;
		y = -1 + (CHAR_HEIGHT * -1);
	}
	else if (direction == UP)
	{
		//	y = 1;
		z = -1;
	}
	else if (direction == DOWN)
	{
		z = 1;
		y = -1 + (CHAR_HEIGHT * -1);
	}
	Vector3 playerPos = player->GetTransform().position;
	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{

		if (Cube* cube = dynamic_cast<Cube*>(*itr))
		{
			Vector3 cubePos = (*itr)->GetTransform().position;
			if (cubePos.x == position.x + x && cubePos.y == position.y + y && cubePos.z == position.z + z)
			{
				return index;
			}
		}
		index++;
	}
	return -1;
}

void Game::UpdateImpl(float dt)
{

	InputManager::GetInstance()->Update(dt);


	if (!player->IsAlive())
	{
		return;
	}

	Vector3 playerPosition = player->GetTransform().position;
	if (InputManager::GetInstance()->GetKeyState(SDLK_UP, SDL_KEYUP) == true)
	{
		int pathIndex = GetPathIndex(playerPosition, UP);
		if (pathIndex > -1)
		{
			Cube* cube = dynamic_cast<Cube*>(_objects[pathIndex]);
			_soundHelper->PlaySound(Move);
			player->Move(UP);

			if (!cube->isVisited)
			{
				cube->ChangeColor();
				++visitedFloors;
			}
		}
		else {
			_soundHelper->PlaySound(Dead);
			player->Die();
			UpdateTitle();
		}
	}
	else if (InputManager::GetInstance()->GetKeyState(SDLK_DOWN, SDL_KEYUP) == true)
	{
		int pathIndex = GetPathIndex(playerPosition, DOWN);
		if (pathIndex > -1)
		{
			Cube* cube = dynamic_cast<Cube*>(_objects[pathIndex]);
			_soundHelper->PlaySound(Move);
			player->Move(DOWN);
			if (!cube->isVisited)
			{
				cube->ChangeColor();
				++visitedFloors;
			}
		}
		else {
			_soundHelper->PlaySound(Dead);
			player->Die();
			UpdateTitle();
		}
	}
	else if (InputManager::GetInstance()->GetKeyState(SDLK_LEFT, SDL_KEYUP) == true)
	{
		int pathIndex = GetPathIndex(playerPosition, LEFT);
		if (pathIndex > -1)
		{
			Cube* cube = dynamic_cast<Cube*>(_objects[pathIndex]);
			_soundHelper->PlaySound(Move);
			player->Move(LEFT);
			if (!cube->isVisited)
			{
				cube->ChangeColor();
				++visitedFloors;
			}
		}
		else {
			_soundHelper->PlaySound(Dead);
			player->Die();
			UpdateTitle();
		}
	}
	else if (InputManager::GetInstance()->GetKeyState(SDLK_RIGHT, SDL_KEYUP) == true)
	{
		int pathIndex = GetPathIndex(playerPosition, RIGHT);
		if (pathIndex > -1)
		{
			Cube* cube = dynamic_cast<Cube*>(_objects[pathIndex]);
			_soundHelper->PlaySound(Move);
			player->Move(RIGHT);
			if (!cube->isVisited)
			{
				cube->ChangeColor();
				++visitedFloors;
			}
		}
		else {
			_soundHelper->PlaySound(Dead);
			player->Die();
			UpdateTitle();
		}
	}

	bool enemyMoved = false;
	for (int enemyIndex = 0; enemyIndex < currentLevel; enemyIndex++)
	{
		Enemy* enemy = enemies[enemyIndex];

		if (enemy == nullptr && lastEnemySpawnTime >= SPAWN_TIME)
		{
			enemies[enemyIndex] = new Enemy(Vector3(2, 0 + CHAR_HEIGHT, 0));
			enemies[enemyIndex]->Initialize(_graphicsObject);

			lastEnemySpawnTime = 0;
		}
		else if (enemy != nullptr)
		{

			if (enemy->walkTime >= ENEMY_SPEED)
			{
				Vector3 enemyPos = enemy->GetTransform().position;

				int range = 3 - 0 + 1;
				int directionValue = rand() % range + 0;
				int pathIndex = -1;
				do
				{
					directionValue = rand() % range + 0;
					pathIndex = GetPathIndex(enemyPos, (Direction)directionValue);
				} while (pathIndex < 0);

				if (pathIndex > -1)
				{
					enemy->Move((Direction)directionValue);
					enemy->walkTime = 0;

				}
			}
			enemy->walkTime += dt;
		}

	}
	lastEnemySpawnTime += dt;

	if (visitedFloors == 15)
	{
		NextLevel();
	}

	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{
		(*itr)->Update(dt);
	}

	for (int enemyIndex = 0; enemyIndex < MAX_ENEMIES; enemyIndex++)
	{
		if (enemies[enemyIndex] == nullptr)
		{
			break;
		}
		enemies[enemyIndex]->Update(dt);
	}
}



void Game::DrawImpl(Graphics *graphics, float dt)
{
	std::vector<GameObject *> renderOrder = _objects;
	//CalculateDrawOrder(renderOrder);

	glPushMatrix();

	CalculateCameraViewpoint();

	for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
	{
		(*itr)->Draw(graphics, _camera->GetProjectionMatrix(), dt);
	}

	for (int enemyIndex = 0; enemyIndex < MAX_ENEMIES; enemyIndex++)
	{
		if (enemies[enemyIndex] == nullptr)
		{
			break;
		}
		enemies[enemyIndex]->Draw(graphics, _camera->GetProjectionMatrix(), dt);
	}

	glPopMatrix();


	if (!player->IsAlive() && !messageShowed)
	{
		GameOver();

	}
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
	// SUPER HACK GARBAGE ALGO.
	drawOrder.clear();

	auto objectsCopy = _objects;
	auto farthestEntry = objectsCopy.begin();
	while (objectsCopy.size() > 0)
	{
		bool entryFound = true;
		for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
		{
			if (farthestEntry != itr)
			{
				if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
				{
					entryFound = false;
					farthestEntry = itr;
					break;
				}
			}
		}

		if (entryFound)
		{
			GameObject *farthest = *farthestEntry;

			drawOrder.push_back(farthest);
			objectsCopy.erase(farthestEntry);
			farthestEntry = objectsCopy.begin();
		}
	}
}

void Game::CalculateCameraViewpoint()
{
	Vector4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);

	Vector3 cameraVector(_camera->GetLookAtVector().x, _camera->GetLookAtVector().y, _camera->GetLookAtVector().z);
	Vector3 lookAtVector(0.0f, 0.0f, -1.0f);

	Vector3 cross = Vector3::Normalize(Vector3::Cross(cameraVector, lookAtVector));
	float dot = MathUtils::ToDegrees(Vector3::Dot(lookAtVector, cameraVector));

	glRotatef(cross.x * dot, 1.0f, 0.0f, 0.0f);
	glRotatef(cross.y * dot, 0.0f, 1.0f, 0.0f);
	glRotatef(cross.z * dot, 0.0f, 0.0f, 1.0f);

	glTranslatef(-_camera->GetPosition().x, -_camera->GetPosition().y, -_camera->GetPosition().z);
}
void Game::NextLevel()
{
	_soundHelper->PlaySound(FinishLevel);
	currentLevel++;
	ClearScenario();
	UpdateTitle();
}

void Game::ClearScenario()
{
	//clearing (reseting) the scenario, enemies and cubes..
	visitedFloors = 0;
	lastEnemySpawnTime = 0;

	for (int enemyIndex = 0; enemyIndex < currentLevel; enemyIndex++)
	{
		enemies[enemyIndex] = nullptr;
	}

	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{
		if (Cube* cube = dynamic_cast<Cube*>(*itr))
		{

			(*itr)->Initialize(_graphicsObject);
		}
	}
	player->RestartPosition();

	UpdateTitle();
}

void Game::GameOver()
{
	_soundHelper->PlaySound(EndGame);

	//displaying a messagebox asking the user if he wants to play again..
	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("Error displaying message box");
	}

	messageShowed = true;

	if (buttons[buttonid].buttonid == 0)
	{
		GameEngine::Shutdown();

		return;
	}
	else if (buttons[buttonid].buttonid == 1)
	{
		Restart();
	}
}

void Game::UpdateTitle()
{
	//updating the title with the current life and level
	std::string title = "My QBert - Life: " + std::to_string(player->GetLife()) + " | Level: " + std::to_string(currentLevel);
	strcpy(_windowTitle, title.c_str());
	SDL_SetWindowTitle(_window, _windowTitle);
}

void Game::Restart()
{
	//restarting the game
	messageShowed = false;
	currentLevel = 1;
	player->Initialize(_graphicsObject);
	ClearScenario();


}