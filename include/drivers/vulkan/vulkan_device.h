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

	struct SwapchainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	struct SwapchainBundle
	{
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		vk::Format format;
		vk::Extent2D extent;
	};

	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool debug);
	bool isSuitable(const vk::PhysicalDevice& device, const bool debug);
	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug);
	QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug);
	vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug);
	std::array<vk::Queue, 2> get_queue(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, vk::Device devie, bool debug);
	SwapchainSupportDetails query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug);
	vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats);
	vk::Extent2D choose_spwapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities);
	SwapchainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height, bool debug);
}

#endif