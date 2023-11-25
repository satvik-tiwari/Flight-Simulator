///////////////////////////////////////////////////
//
//	Hamish Carr
//	January, 2018
//
//	------------------------
//	main.cpp
//	------------------------
//	
///////////////////////////////////////////////////

#include <QtWidgets/QApplication>
#include "FlightSimulatorWidget.h"
#include "SceneModel.h"
#include <iostream>
#include <string>
#include <cstdlib>

int main(int argc, char **argv)
	{ // main()
	// initialize QT
	//for(int i = 0; i < 4; i++)
	//std::cout << argv[i] << std::endl;
	
	QApplication app(argc, argv);
	
	
	//	create a window
	try
		{ // try block
		// we want a single instance of the scene model
		SceneModel theScene(std::atof(argv[1]), -(std::atof(argv[2])), std::atof(argv[3]));
		
		// create the widget with no parent
		FlightSimulatorWidget flightWindow(NULL, &theScene);
		
		// 	set the initial size
		flightWindow.resize(600, 600);

		// show the window
		flightWindow.show();

		// set QT running
		return app.exec();
		
		
		} // try block
	catch (std::string errorString)
		{ // catch block
		std::cout << "Unable to run application." << errorString << std::endl;
		} // catch block
	
	// paranoid return value
	exit(0);
	} // main()
