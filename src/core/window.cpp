#include "core/window.h"

namespace O1F4Engine
{
	Window::Window(int width, int height, std::string title, bool isDebug) {
		// Initialize glfw
		glfwInit();

		// No default rendering client, we'll hook vulkan up
		// To make the window later
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		// Resizing breaks the swapchain, we'll disable it for now
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, "On1Four Engine", nullptr, nullptr);

		if (window)
		{
			if (isDebug)
			{
				std::cout << "Successfully made a glfw window\n";
			}
		}
		else
		{
			if (isDebug)
			{
				std::cout << "Failed to create GLFW window\n";
			}
		}
	}

	GLFWwindow* Window::get_window()
	{
    return window;
	}
}