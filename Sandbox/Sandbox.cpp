#include <Engine.h>
#include "Scenes/ExampleScene.h"
#include "Scenes/VolumeRendering.h"


class SandboxApp : public Engine::Application {
public:
	SandboxApp() : Engine::Application() {

	}

	~SandboxApp() override {

	}

	void run() override {
		Engine::Window window("App",1600,900,false,false, true);

		VolumeRendering scene("Volume Rendering", window);

		Engine::SceneManager::pushScene(&scene);

		OutputDebugString(L"WTF");

		while (!window.ShouldClose()) {
			window.Update();

			window.PostEvents();
		}

		Engine::SceneManager::clearAll();
	}
};

Engine::Application* Engine::CreateApplication() {
	return new SandboxApp();
}