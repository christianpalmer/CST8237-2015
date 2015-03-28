/**
* \class Enemy.h
* \brief An class that represents an enemy
* to be placed and manipulated in the world.
* \author Christian Andrade
* \date March 23, 2015
*/

#pragma once

#include <GameObject.h>

struct Vertex;

class Enemy : public GameObject
{
public:
	Enemy();
	Enemy(Vector3 position);
	float walkTime;

	/**
	* \fn void Initialize()
	* \brief A virtual function that we’ll use as to define how our
	* object is initialized.
	*/

  void Initialize(Graphics *graphics);

  /**
  * \fn void Update(float dt)
  * \brief A virtual function that we’ll use as to define how our
  * object is updated
  * \param dt The time in fractions of a second since the last pass.
  */
  void Update(float dt);

  /**
  * \fn void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
  * \brief A virtual function that we’ll use as to define how our
  * object is drawn to the screen.
  * \param graphics is an object with the properties used to draw the object.
  * \param relativeTo is a matrix object
  * \param dt The time in fractions of a second since the last pass.
  */
  void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

  /**
  * \fn void Move(Direction direction)
  * \brief A function used to move the player
  * \param direction, the direction to which the player will move
  */
  void Move(Direction direction);

protected:

  Vector3 *vertices;
  Vector4 *colours;
  
  
  int size;
  int offset;
  

  unsigned int* indices;

  void SetVertex(int index, float x, float y, float z, float r, float g, float b, float a);

};