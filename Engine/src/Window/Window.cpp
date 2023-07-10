#include "Window.h"
#include <iostream>
#include "Log.h"
#include "Input/InputHandler.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"
#include "Scene/SceneManager.h"

#ifdef GRAPHICS_API_OPENGL
#include "GUI/ImGuiLayer.h"
#include "GUI/DockSpace.h"
#elif GRAPHICS_API_DIRECTX
//TODO Alperen
#endif 

Engine::Window::Window(std::string name, uint32_t width, uint32_t height, bool fullscreen, bool vsync, bool dockspaceEnabled) {
	properties.name = name;
	properties.width = width;
	properties.height = height;
	properties.vsync = vsync;
	properties.fullscreen = fullscreen;
	properties.dockspaceEnabled = dockspaceEnabled;

	if (glfwInit() != GLFW_TRUE) {
		ENG_LOG_ERROR("Failed to initialize GLFW");
		return;
	}

	ENG_LOG_INFO("GLFW is successfuly initialized");

	//TODO Window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	if (fullscreen) {
		properties.nativeWindowPtr = glfwCreateWindow(width, height, name.c_str(), glfwGetPrimaryMonitor(), nullptr);
	}
	else {
		properties.nativeWindowPtr = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
	}

	if (properties.nativeWindowPtr == nullptr) {
		glfwTerminate();
		ENG_LOG_ERROR("Failed to create window: {0}, ({1},{2})", name, width, height);

		return;
	}

	ENG_LOG_INFO("Window is created successfully: {0}, ({1},{2})", name, width, height);

	glfwMakeContextCurrent(properties.nativeWindowPtr);

#ifdef GRAPHICS_API_OPENGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		ENG_LOG_ERROR("Failed to initialize GLAD and OpenGL!!!");
		glfwTerminate();

		return;
	}

#elif GRAPHICS_API_DIRECTX
	HWND hWnd = glfwGetWin32Window(properties.nativeWindowPtr);
	pGfx = new DX::Direct3D11(hWnd, width, height);
#endif 

	glfwSetWindowUserPointer(properties.nativeWindowPtr, &properties);

	//glViewport(0, 0, properties.width, properties.height);

	
	if (vsync) 
		glfwSwapInterval(1);
	else 
		glfwSwapInterval(0);
		

	//glEnable(GL_DEPTH_TEST);

	InputHandler::Init();

	AddCallbackFunctions();

	//glDepthFunc(GL_LEQUAL);


#ifdef GRAPHICS_API_OPENGL
	ImGuiLayer::InitImGui(*this);
#elif GRAPHICS_API_DIRECTX
	//TODO Alperen
#endif 

	time_now = (float)glfwGetTime();
}

void Engine::Window::AddCallbackFunctions() {
	glfwSetKeyCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			KeyPressedEvent event(key);
#ifdef LOG_INPUTS
			ENG_LOG_INFO(event.getMessage());
#endif
		}
		else if (action == GLFW_REPEAT) {
			KeyRepeatedEvent event(key);
#ifdef LOG_INPUTS
			ENG_LOG_INFO(event.getMessage());
#endif
		}
		if (action == GLFW_RELEASE) {
			KeyReleasedEvent event(key);
#ifdef LOG_INPUTS
			ENG_LOG_INFO(event.getMessage());
#endif
		}
		});

	glfwSetCursorPosCallback(properties.nativeWindowPtr, [](GLFWwindow* window, double xpos, double ypos) {
		MouseMovedEvent event((float)xpos, (float)ypos);

#ifdef LOG_INPUTS
		ENG_LOG_INFO(event.getMessage());
#endif
		});

	glfwSetScrollCallback(properties.nativeWindowPtr, [](GLFWwindow* window, double xoffset, double yoffset) {
		MouseScrolledEvent event((float)xoffset, (float)yoffset);

#ifdef LOG_INPUTS
		ENG_LOG_INFO(event.getMessage());
#endif
		});

	glfwSetMouseButtonCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			MouseButtonPressedEvent event(button);

#ifdef LOG_INPUTS
			ENG_LOG_INFO(event.getMessage());
#endif
		}
		else if (action == GLFW_RELEASE) {
			MouseButtonReleasedEvent event(button);

#ifdef LOG_INPUTS
			ENG_LOG_INFO(event.getMessage());
#endif
		}
		});

	glfwSetWindowCloseCallback(properties.nativeWindowPtr, [](GLFWwindow* window) {
		WindowClosedEvent event;

#ifdef LOG_INPUTS
		ENG_LOG_INFO(event.getMessage());
#endif
		});

	glfwSetWindowSizeCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int width, int height) {
		WindowResizedEvent event(width, height);

#ifdef LOG_INPUTS
		ENG_LOG_INFO(event.getMessage());
#endif
		});

	glfwSetWindowPosCallback(properties.nativeWindowPtr, [](GLFWwindow* window, int xpos, int ypos) {
		WindowMovedEvent event(xpos, ypos);

#ifdef LOG_INPUTS
		ENG_LOG_INFO(event.getMessage());
#endif
		});


#ifdef GRAPHICS_API_OPENGL
	glEnable(GL_DEBUG_OUTPUT); //Opengl Debug callback to trace errors
	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const  GLchar* message, const void* userParam) {

		if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) {
			ENG_LOG_ERROR("OpenGL Debug Message:");
			ENG_LOG_ERROR("Source: {0}", source);
			ENG_LOG_ERROR("Type: {0}", type);
			ENG_LOG_ERROR("ID: {0}", id);
			ENG_LOG_ERROR("Severity: {0}", severity);
			ENG_LOG_ERROR("Message: {0}", message);
			ENG_LOG_ERROR("------------------------");
		}
		}, nullptr);
#elif GRAPHICS_API_DIRECTX
	//TODO Alperen
#endif

}

Engine::Window::~Window() {

#ifdef GRAPHICS_API_OPENGL
	ImGuiLayer::Shutdown();
#elif GRAPHICS_API_DIRECTX
	delete pGfx;
#endif 


	glfwDestroyWindow(properties.nativeWindowPtr);
	ENG_LOG_INFO("Window is destoryed: {0}, ({1},{2})", properties.name, properties.width, properties.height);
	glfwTerminate();

	ENG_LOG_INFO("GLFW is terminated");
}

GLFWwindow* Engine::Window::GetNativeWindowPtr() {
	return properties.nativeWindowPtr;
}

void Engine::Window::Update() {
#ifdef GRAPHICS_API_OPENGL
	glClearColor(0.1f, 0.5f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
#elif GRAPHICS_API_DIRECTX
	pGfx->BeginFrame();
#endif 

	time_prev = time_now;
	time_now = (float)glfwGetTime();

	deltaTime = time_now - time_prev;

	glfwPollEvents();

#ifdef GRAPHICS_API_OPENGL
	ImGuiLayer::StartNewFrame();

	if (properties.dockspaceEnabled)
		Dockspace::begin(*this);
#elif GRAPHICS_API_DIRECTX

#endif 

	SceneManager::update(deltaTime);
}

void Engine::Window::PostEvents() {

#ifdef GRAPHICS_API_OPENGL
	if (properties.dockspaceEnabled)
		Dockspace::end();
	ImGuiLayer::RenderNewFrame();
	glfwSwapBuffers(properties.nativeWindowPtr);
#elif GRAPHICS_API_DIRECTX
	pGfx->EndFrame();
#endif

	InputHandler::UpdateTemporaryBuffers();
}

float Engine::Window::GetDeltaTime()
{
	return deltaTime;
}

void Engine::Window::Resize(const uint32_t width, const uint32_t height) {
	properties.width = width;
	properties.height = height;

	glfwSetWindowSize(properties.nativeWindowPtr, width, height);
}

bool Engine::Window::ShouldClose()
{
	return glfwWindowShouldClose(properties.nativeWindowPtr);
}

Engine::Window::WindowProperties Engine::Window::getWindowProperties()
{
	return properties;
}

#if GRAPHICS_API_DIRECTX
DX::Direct3D11& Engine::Window::Gfx()
{
	return *pGfx;
}
#endif
