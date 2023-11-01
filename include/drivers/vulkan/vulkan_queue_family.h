#ifndef VULKAN_QUEUE_FAMILY_H
#define VULKAN_QUEUE_FAMILY_H

#include <of_pch.h>

namespace O1F4Engine
{
	namespace O1F4Render
	{	
		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;

			bool isComplete()
			{
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};

		QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug);
	}
}

#endif //VULKAN_QUEUE_FAMILY