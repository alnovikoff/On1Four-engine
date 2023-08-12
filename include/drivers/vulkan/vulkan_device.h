#ifndef VULKAN_DEVICE
#define VULKAN_DEVICE

#include <of_pch.h>

namespace O1F4Vulkan
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

	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool debug);
	bool isSuitable(const vk::PhysicalDevice& device, const bool debug);
	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);

	QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug);
}

#endif