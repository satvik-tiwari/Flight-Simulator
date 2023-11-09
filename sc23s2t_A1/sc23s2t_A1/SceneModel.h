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

	// a matrix that specifies the mapping from world coordinates to those assumed
	// by OpenGL
	Matrix4 world2OpenGLMatrix;
	
	// constructor
	SceneModel();

	// routine that updates the scene for the next frame
	void Update();

	// routine to tell the scene to render itself
	void Render();

	}; // class SceneModel

#endif
