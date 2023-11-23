///////////////////////////////////////////////////
//
//	Hamish Carr
//	October, 2023
//
//	------------------------
//	SceneModel.cpp
//	------------------------
//	
//	The model of the scene
//
//	
///////////////////////////////////////////////////

#include "SceneModel.h"
#include <math.h>
//#include <fstream>
// three local variables with the hardcoded file names
const char *groundModelName 	= "./models/landscape.dem";
const char *planeModelName 		= "./models/planeModel.tri";
const char *lavaBombModelName 	= "./models/lavaBombModel.tri";

const Homogeneous4 sunDirection(0.0, 0.3, 0.3, 1.0);
const GLfloat groundColour[4] = { 0.2, 0.6, 0.2, 1.0 };
const GLfloat sunAmbient[4] = {0.1, 0.1, 0.1, 1.0 };
const GLfloat sunDiffuse[4] = {0.7, 0.7, 0.7, 1.0 };
const GLfloat blackColour[4] = {0.0, 0.0, 0.0, 1.0};
const GLfloat lavaBombColour[4] = {0.5, 0.3, 0.0, 1.0};
const GLfloat planeColour[4] = {0.1, 0.1, 0.5, 1.0};
const GLfloat planeRadius = 2.0;
const GLfloat lavaBombRadius = 100.0;
const Cartesian3 chaseCamVector(0.0, -2.0, 0.5);

// constructor
SceneModel::SceneModel()
	{ // constructor
	// this is not the best place to put this in general, but this is a quick and dirty hack
	// we start by loading three files: one for each model
	groundModel.ReadFileTerrainData(groundModelName, 500);
	planeModel.ReadFileTriangleSoup(planeModelName);
	lavaBombModel.ReadFileTriangleSoup(lavaBombModelName);
	
//	When modelling, z is commonly used for "vertical" with x-y used for "horizontal"
//	When rendering, the default is that we render using screen coordinates, so x is to the right,
//	y is up, and z points behind us by the right hand rule.  That means when looking into the screen,
//	we are actually looking out along the z-axis
//	That means we will have to start off with a view matrix that compensates for this
//	Assume that we want to look out along the y axis with the z axis pointing up instead
//	Then the x-axis is off to the right.  This means that our mapping is as follows:
//		x is unchanged	from WCS					to VCS
//		y was forward 	in WCS		is now up		in VCS
//  	z was up		in WCS		is now back		in VCS
//	because x is unchanged, this is a rotation around x, with y moving towards z, so it is a
//	rotation of 90 degrees CCW

	// set the world to opengl matrix
	world2OpenGLMatrix = Matrix4::RotateX(90.0);
	camPos = Matrix4::Identity();
	viewMatrix = camPos.transpose();
	
	translation = Matrix4::Translate(Cartesian3(0.0f, 0.0f, 0.0f));
	rotation = Matrix4::Identity();
	scale = Matrix4::Identity();
	modelView = Matrix4::Identity();
	

	} // constructor



// routine that updates the scene for the next frame
void SceneModel::Update()
	{ // Update()
			
		//create view matrix
		s += 100.0f;
		r+= 0.1f;
		//Matrix4 viewMatrix;
		viewMatrix = camPos.transpose();
		
		//model matrix = translation * rotation * scale
		
		translation = Matrix4::Translate(Cartesian3(0.0f, s, 0.0f));
		rotation = Matrix4::RotateY(r);
		scale = Matrix4::Identity();
		//modelMatrix = translation * rotation * scale;
				modelMatrix = scale * rotation * translation;
		modelView = viewMatrix * modelMatrix;
		//groundModel.Render(world2OpenGLMatrix);
		//Matrix4 m = modelView * world2OpenGLMatrix;
		//planeModel.Render(m);
		
		camPos = viewMatrix;
	//	world2OpenGLMatrix = Matrix4::RotateY(s);
	
		
		//world2OpenGLMatrix = Matrix4::RotateX(90.0);
		//groundModel.Render(world2OpenGLMatrix);
		
		
		std::cout << "modelView:\n" << modelView << "\n" << std::endl;
		
	} // Update()

// routine to tell the scene to render itself
void SceneModel::Render()
	{ // Render()
	// enable Z-buffering
	glEnable(GL_DEPTH_TEST);
	
	// set lighting parameters
	glShadeModel(GL_FLAT);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sunDiffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, blackColour);
	glLightfv(GL_LIGHT0, GL_EMISSION, blackColour);
	
	// background is sky-blue
	glClearColor(0.7, 0.7, 1.0, 1.0);

	// clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// compute the light position
  	Homogeneous4 lightDirection = world2OpenGLMatrix * sunDirection;
	// and set the w to zero to force infinite distance
 	lightDirection.w = 0.0;
 	 	
	// pass it to OpenGL
	glLightfv(GL_LIGHT0, GL_POSITION, &(lightDirection.x));

	// and set a material colour for the ground
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, groundColour);
	glMaterialfv(GL_FRONT, GL_SPECULAR, blackColour);
	glMaterialfv(GL_FRONT, GL_EMISSION, blackColour);

	// actual render code goes here
	groundModel.Render(world2OpenGLMatrix);
	planeModel.Render(modelView);

	} // Render()	
	
	
		
/*	Matrix4 kglm::lookAt(Cartesian3 eye, Cartesian3 at, Cartesian3 up)
	{
	 Cartesian3 zaxis = (at - eye).unit();
	 Cartesian3 xaxis = (zaxis.cross(up)).unit();
	 Cartesian3 yaxis = xaxis.cross(zaxis);
	 
	 -zaxis; 
	 
	 //std::ofstream destination;
	 //destination.open("Dump.txt");
	 //destination << "Homogenesous coords \n" 
	 //						<< Homogeneous4(xaxis.x, xaxis.y, xaxis.z, -xaxis.dot(eye));
		//std::cout << "Homogeneouss coords " << Homogeneous4(xaxis.x, xaxis.y, xaxis.z, -xaxis.dot(eye));
  Matrix4 viewMatrix;
  viewMatrix.Identity();
  
	
	
	
	//writing all the blocks one by one to .face file
		
  Homogeneous4 h0 = Homogeneous4(xaxis.x, xaxis.y, xaxis.z, -xaxis.dot(eye));
  
  Homogeneous4 h1 = Homogeneous4(yaxis.x, yaxis.y, yaxis.z, -yaxis.dot(eye));
  
  Homogeneous4 h2 = Homogeneous4(zaxis.x, zaxis.y, zaxis.z, -zaxis.dot(eye));
  
  Homogeneous4 h3 = Homogeneous4(0, 0, 0, 1);
  
  
	viewMatrix = Matrix4::Homogeneous2Mat(h0, h1, h2, h3);
  return viewMatrix;
	  
	}
*/
