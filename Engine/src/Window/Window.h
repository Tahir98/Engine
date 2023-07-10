#pragma once

#ifdef GRAPHICS_API_OPENGL
#include <glad/glad.h>
#elif GRAPHICS_API_DIRECTX
#define GLFW_EXPOSE_NATIVE_WIN32
#include "Graphics\DirectX11\Direct3D11.h"
#include <glad/glad.h> //tmp
#endif 

#include <GLFW/glfw3.h>
#include  <GLFW\glfw3native.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>

#ifndef LOG_INPUTS
	//#define LOG_INPUTS
#endif // !LOG_INPUTS


namespace Engine {
	class Window {
	public:
		struct WindowProperties {
			std::string name;
			uint32_t width, height;
			GLFWwindow* nativeWindowPtr = nullptr;
			bool fullscreen;
			bool vsync;
			bool dockspaceEnabled;
		};
	private:
		WindowProperties properties;
		float deltaTime;
		float time_prev = 0, time_now = 0;

		void AddCallbackFunctions();
	public:

		Window(std::string name, uint32_t width, uint32_t height, bool fullscreen, bool vsync = true, bool dockspaceEnabled = true);
		~Window();

		GLFWwindow* GetNativeWindowPtr();

		void Update();
		void PostEvents();
		float GetDeltaTime();
		void Resize(const uint32_t width, const uint32_t height);
		bool ShouldClose();
		WindowProperties getWindowProperties();

#if GRAPHICS_API_DIRECTX
		DX::Direct3D11& Gfx();
#endif 

	private:
#if GRAPHICS_API_DIRECTX
		DX::Direct3D11* pGfx;
#endif 
	};
}


