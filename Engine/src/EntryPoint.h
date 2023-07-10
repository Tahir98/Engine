#pragma once

#include "Application.h"
#include "Log.h"

int main(int args, char** argv) {
	Engine::Log::init();

	Engine::Application* app = Engine::CreateApplication();

	if (app != nullptr)
	{
		app->run();
	}

	delete app;

	return 0;
}