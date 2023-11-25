# University of Leeds 2023-24
# COMP 5823M Assignment 1 Flight Simulator
# Satvik Tiwari
# 201791342


================================================

LINUX :

To compile on the University Linux machines, you will need to do the following:

[userid@machine A1_handout]$ module add legacy-eng
[userid@machine A1_handout]$ module add qt/5.15.2
[userid@machine A1_handout]$ qmake -project QT+=opengl LIBS+=-lGLU
[userid@machine A1_handout]$ qmake
[userid@machine A1_handout]$ make

To execute the programe:

[userid@machine A1_handout]$ ./A1_handout X Y Z

Y increses with alitude so, enter Y in positve, without negative sign.

=======================================================

AXES

Forward is -Z
Up is Y
Right is X

========================================================

A : Pitch up
S : Pitch Down

W : Yaw left
D : Yaw right

Q : Roll left
R : Roll right

Q : Quit

0-9 : Set speed from 0 to 9 m/s depending on which key use press from '0' to '9'
+ : Increse speed by 1 m/s
- : Decrease speed by 1 m/s

=====================================================================
The lava bombs are being originated at tip of volcano at (-38500.0, 625.0, -4000.0)

Note - particle system not working

Psudo code for the same -

Particle
{
 Matrix4 modelMatrix;
 bool isDead;
 float age;
 float lifespan;
	float delay;
	float speed;	
}

Scene::GetNewParticle()
{
 //initialize the paritcle
}

Scene::Scene() //constructor
{

vector of Particle type; 

//for each index in the vector GetNewParticle()
//initialize the particles based on monte carlo distribution
//also add a random delay
}

Update()
{
	for(i = 0; i < paritcles.size(); i++)
	{
	 if(particle reached maximum height)
	 {
	 	particles[i].isdead = true;
	 	
	 	//newParticlesEmergefromhere
	 	
	 }
	 
	 //no nedd to calculate model matrix until the dealy is over
	 if(delay<0)
	 {
	  if(partilces[i].isdead)
	  {
	   // if a particle is dead, replace it with new one
	    GetNewParticle()
	  }
		
		speed++
		
		//calculate model matrix
		
	 }								
		
	
	}
	
	else
	
	delay--
}

Render()
{
foreach(particle in Particles)
{
 if(!isDead)
 {
  LavaBomb.Render(paricle.modelMatrix * viewMatrixOfCamera);
 }
}

}


=====================================================================


