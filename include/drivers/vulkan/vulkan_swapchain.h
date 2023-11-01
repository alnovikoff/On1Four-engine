#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include <of_pch.h>
#include <drivers/vulkan/vulkan_frame.h>

namespace O1F4Engine
{
	namespace O1F4Render
	{
		struct SwapchainSupportDetails
		{
			vk::SurfaceCapabilitiesKHR capabilities;
			std::vector<vk::SurfaceFormatKHR> formats;
			std::vector<vk::PresentModeKHR> presentModes;
		};

		struct SwapchainBundle
		{
			vk::SwapchainKHR swapchain;
			std::vector<O1F4Engine::O1F4Render::SwapchainFrame> frames;
			vk::Format format;
			vk::Extent2D extent;
		};

		SwapchainSupportDetails query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug);
		vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats);
		vk::Extent2D choose_spwapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities);
		SwapchainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height, bool debug);
	}
}

#endif //VULKAN_SWAPCHAIN_H