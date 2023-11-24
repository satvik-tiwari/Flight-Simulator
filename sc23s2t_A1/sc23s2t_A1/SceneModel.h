///////////////////////////////////////////////////
//
//	Hamish Carr
//	October, 2023
//
//	------------------------
//	SceneModel.h
//	------------------------
//	
//	The model of the scene
//	
///////////////////////////////////////////////////

#ifndef __SCENE_MODEL_H
#define __SCENE_MODEL_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include "HomogeneousFaceSurface.h"
#include "Terrain.h"

#include "Matrix4.h"

#include "Random.h"



class SceneModel										
	{ // class SceneModel
	public:	
	// we'll have three geometric surfaces: one for the ground (and volcano)
	// one for the plane 
	// and one for the lava bomb(s)
	
	
	
	Terrain groundModel;
	HomogeneousFaceSurface planeModel;
	HomogeneousFaceSurface lavaBombModel;
	
	
	//iniital position of plane
	float initial_x, initial_y, initial_z;
	

	// a matrix that specifies the mapping from world coordinates to those assumed
	// by OpenGL
	Matrix4 world2OpenGLMatrix;
	
	//Matrix4 camPos;
	Matrix4 viewMatrix;
	Matrix4 modelMatrix;
	Matrix4 modelView;
	
	Matrix4 translation;
	Matrix4 rotation;
	Matrix4 scale;
		
	float speed;
	float speed_increment_factor;
	//float r = 0.0f;
	
	// constructor
	SceneModel(float x, float y, float z);

	// routine that updates the scene for the next frame
	void Update();

	// routine to tell the scene to render itself
	void Render();
	
	void SetSpeed(float s);
	
	Matrix4 lookAt(Cartesian3 eye, Cartesian3 at, Cartesian3 up);

	}; // class SceneModel
/*	
class kglm
{
	public:
	static Matrix4 lookAt(Cartesian3 eye, Cartesian3 at, Cartesian3 up);
};
*/
#endif
