#ifndef WINDOW_H
#define WINDOW_H

#include <of_pch.h>
#include <core/defines.h>

namespace O1F4Engine
{
	namespace O1F4PAL
	{
		class ON1F_API Window
		{
		public:
			Window(int width, int height, std::string title, bool isDebug);

			void build_glfw_window();
			void run();

			GLFWwindow* get_window();

		private:
			int width;
			int height;
			GLFWwindow *window{nullptr};;
		};
	}
}

#endif // WINDOW_H