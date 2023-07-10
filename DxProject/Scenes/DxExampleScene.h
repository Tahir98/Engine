#pragma once

#pragma once
#include "Engine.h"
#include "Graphics\DirectX11\Direct3D11.h"

class DxExampleScene : public Engine::Scene {
private:

public:
	DxExampleScene(std::string name, Engine::Window& window) : Scene(name, window) {
		APP_LOG_INFO("Scene constructor is called, name: {0}, id: {1}", name, id);
	}

	~DxExampleScene() override {
		APP_LOG_INFO("Scene destructor is called, name: {0}, id: {1}", name, id);
	}

	void OnCreate() override {
		APP_LOG_INFO("Scene OnCreate method is called, name: {0}, id: {1}", name, id);
	}

	void OnUpdate(float delta) override {
		APP_LOG_INFO("Scene OnUpdate method is called, name: {0}, id: {1}, delta time: {2}", name, id, delta);
	}

	void OnSuspend() override {
		APP_LOG_INFO("Scene OnSuspend method is called, name: {0}, id: {1}", name, id);
	}

	void OnResume() override {
		APP_LOG_INFO("Scene OnResume method is called, name: {0}, id: {1}", name, id);
	}

	void OnDestroy() override {
		APP_LOG_INFO("Scene OnDestroy method is called, name: {0}, id: {1}", name, id);
	}
};
