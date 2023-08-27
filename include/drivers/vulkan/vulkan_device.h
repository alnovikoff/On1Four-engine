#ifndef VULKAN_DEVICE_H
#define VULKAN_DEVICE_H

#include <of_pch.h>

namespace O1F4Vulkan
{
	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool debug);
	bool isSuitable(const vk::PhysicalDevice& device, const bool debug);
	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);
	vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug);
	std::array<vk::Queue, 2> get_queue(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, vk::Device devie, bool debug);
}

#endif