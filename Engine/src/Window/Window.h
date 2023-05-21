#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

#ifndef LOG_INPUTS
	#define LOG_INPUTS
#endif // !LOG_INPUTS


namespace Engine {
	class Window {
	private:
		struct WindowProperties {
			std::string name;
			uint32_t width, height;

			GLFWwindow* nativeWindowPtr = nullptr;
		};

		WindowProperties properties;
		float deltaTime;
		float time_prev = 0, time_now = 0;

		void AddCallbackFunctions();
	public:

		Window(std::string name, uint32_t width, uint32_t height, bool fullscreen);
		~Window();

		GLFWwindow* GetNativeWindowPtr();

		void Update();
		void PostEvents();
		float GetDeltaTime();
		void Resize(const uint32_t width, const uint32_t height);
		bool ShouldClose();
	};
}

