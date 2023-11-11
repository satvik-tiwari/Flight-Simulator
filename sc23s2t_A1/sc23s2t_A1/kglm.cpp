#include "kglm.h"

namespace kglm
{
	
	Matrix4 lookAt(Cartesian3 eye, Cartesian3 at, Cartesian3 up)
	{
	 Cartesian3 zaxis = (at - eye).unit();
	 Cartesian3 xaxis = (zaxis.cross(up)).unit();
	 Cartesian3 yaxis = xaxis.cross(zaxis);
	 
	 -zaxis; 

  Matrix4 viewMatrix = {
    Homogeneous4(xaxis.x, xaxis.y, xaxis.z, -dot(xaxis, eye)),
    Homogeneous4(yaxis.x, yaxis.y, yaxis.z, -dot(yaxis, eye)),
    Homogeneous4(zaxis.x, zaxis.y, zaxis.z, -dot(zaxis, eye)),
    Homogeneous4(0, 0, 0, 1)
  };

  return viewMatrix;
	  
	}



}
