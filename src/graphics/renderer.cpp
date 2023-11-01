#include <graphics/renderer.h>

#include <drivers/vulkan/vulkan_instance.h>
#include <drivers/vulkan/vulkan_logging.h>
#include <drivers/vulkan/vulkan_device.h>
#include <drivers/vulkan/vulkan_swapchain.h>
#include <graphics/vulkan/vulkan_pipeline.h>

namespace O1F4Engine
{
	namespace O1F4Render
	{
		Renderer::Renderer(GLFWwindow* window, int width, int height, bool isDebug)
		{
			make_render_instance(window, isDebug);
			make_device(800, 600,isDebug);
			make_pipeline(isDebug);
		}

		void Renderer::make_render_instance(GLFWwindow* window, bool isDebugMode)
		{
			instance = create_vulkan_instance(isDebugMode, "On1Four Engine");
			dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);
			if(isDebugMode)
			{
				debugMessenger = O1F4RenderUtils::make_debug_messenger(instance, dldi);
			}
			VkSurfaceKHR c_style_surface;
			if(glfwCreateWindowSurface(instance, window, nullptr, &c_style_surface) != VK_SUCCESS)
			{
				if(isDebugMode)
				{
					std::cout << "Failed to create abstract the glfwsurface for Vulkan\n";
				}
			}
			else
			{
				if(isDebugMode)
				{
					std::cout << "Successfully abstracteds the glfwsurface for Vulkan\n";
				}
			}
			surface = c_style_surface;
		}

		void Renderer::make_device(int width, int height, bool isDebugMode) 
		{
			physicalDevice = choose_physical_device(instance, isDebugMode);
			device = create_logical_device(physicalDevice, surface, isDebugMode);
			std::array<vk::Queue, 2> queues = get_queue(physicalDevice, surface, device, isDebugMode);
			graphicsQueue = queues[0];
			presentQueue = queues[1];
			query_swapchain_support(physicalDevice, surface, true);
			SwapchainBundle bundle = create_swapchain(device, physicalDevice, surface, width, height, isDebugMode);
			swapchain = bundle.swapchain;
			swapchainFrames = bundle.frames;
			swapchainFormat = bundle.format;
			swapchainExtent = bundle.extent;
		}

		void Renderer::make_pipeline(bool isDebugMode)
		{
			GraphicsPipelineInBundle specification = {};
			specification.device = device;
			specification.vertexFilepath = "E:\\MyEngine\\On1Four\\engine\\assets\\shaders\\vertex.spv";
			specification.swapchainExtent = swapchainExtent;

			GraphicsPipelineOutBundle output = make_graphics_pipeline(specification, isDebugMode);
		}

		Renderer::~Renderer()
		{
			for(SwapchainFrame frame : swapchainFrames)
			{
				device.destroyImageView(frame.imageView);
			}
			device.destroySwapchainKHR(swapchain);
			device.destroy();
			instance.destroySurfaceKHR(surface);

			//if(isDebugMode)
			//{
				instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
			//}
			instance.destroy();
			glfwTerminate();
		}
	}
}