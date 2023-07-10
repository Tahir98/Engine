#include <Engine.h>
#include "Scenes/DxExampleScene.h"

class DxApplication : public Engine::Application {
public:
	DxApplication() : Engine::Application() {

	}

	~DxApplication() override {

	}

	void run() override {
		
		try
		{
			Engine::Window window("Directx11 Application", 1600, 900, false, false, true);


			DxExampleScene scene("Example Scene", window);

			Engine::SceneManager::pushScene(&scene);

			while (!window.ShouldClose()) {
				window.Update();

				window.PostEvents();
			}

			Engine::SceneManager::clearAll();
		}
		catch (const std::exception& e)
		{
			MessageBox(nullptr, DX::convertCharArrayToLPCWSTR(e.what()), L"Standart Exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}
};

Engine::Application* Engine::CreateApplication() {
	return new DxApplication();
}