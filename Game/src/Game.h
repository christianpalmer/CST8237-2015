
/**
* \class Game.h
* \brief An class that represent the Game
* \author Christian Andrade
* \date March 23, 2015
*/
#pragma once

#include <GameEngine.h>

union SDL_Event;
class Graphics;
class Camera;
class Game: public GameEngine
{
  friend class GameEngine;


public:
  ~Game();
   SoundHelper* _soundHelper;
 


private:
	void CreateFloors();
	char* _windowTitle;
	void GameOver();
	void ClearScenario();
	void Restart();
	void UpdateTitle();

protected:
  Game();

  void InitializeImpl();
  void UpdateImpl(float dt);
  void DrawImpl(Graphics *graphics, float dt);

  void Reset();
  void CalculateDrawOrder(std::vector<GameObject *>& drawOrder);
  void CalculateCameraViewpoint();

  int GetPathIndex(Vector3 position, Direction direction);

  void NextLevel();

  Camera *_camera;

 
};