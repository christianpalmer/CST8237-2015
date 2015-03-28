/**
* \class Cube.h
* \brief An class that represents a cube (tile)
*   in the world.
* \author Christian Andrade
* \date March 22, 2015
*/

#pragma once

#include <GameObject.h>

struct Vertex;

class Cube : public GameObject
{
public:
	bool isVisited = false;
	Cube();
	Cube(Vector3 position);

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
	* \fn void ChangeColor()
	* \brief A function used to change the color of the cube
	*/
	void ChangeColor();

protected:
	//void *_vertexPointer;

	Vector3 *vertices;
	Vector4 *colours;

	int size;
	int offset;


	//Vertex *vertices;
	unsigned int* indices;

	void SetVertex(int index, float x, float y, float z, float r, float g, float b, float a);
};