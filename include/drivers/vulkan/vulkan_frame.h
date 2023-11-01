#ifndef VULKAN_FRAME_H
#define VULKAN_FRAME_H

#include <of_pch.h>

namespace O1F4Engine
{
	namespace O1F4Render
	{
		struct SwapchainFrame {
			vk::Image image;
			vk::ImageView imageView;
		};
	}
} // namespace O1F4EngineUtil

#endif // VULKAN_LOGGING_H