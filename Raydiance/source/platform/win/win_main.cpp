#include <./pch.h>


#include "./core/application.h"


int main(char* argc, char** argv)
{
	// Create application - user implemented application
	Raydiance::Application* app = CreateApplication();
	//app->Initialize();


	// Garbage
	//app->Terminate();
	delete app;

	return 0;
}