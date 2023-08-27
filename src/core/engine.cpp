#include <core/engine.h>

#include <drivers/vulkan/vulkan_instance.h>
#include <drivers/vulkan/vulkan_logging.h>
#include <drivers/vulkan/vulkan_device.h>

namespace O1F4Engine
{
  Engine::Engine()
  {
    build_glfw_window();

    make_instance();

    make_device();
  }

  void Engine::build_glfw_window()
  {
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
      if (isDebugMode)
      {
        std::cout << "Successfully made a glfw window\n";
      }
    }
    else
    {
      if (isDebugMode)
      {
        std::cout << "Failed to create GLFW window\n";
      }
    }
  }

  void Engine::make_instance()
  {
    instance = O1F4Vulkan::create_vulkan_instance(isDebugMode, "On1Four Engine");
    dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);
    if(isDebugMode)
    {
      debugMessenger = O1F4Vulkan::make_debug_messenger(instance, dldi);
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

  void Engine::make_device() 
  {
    physicalDevice = O1F4Vulkan::choose_physical_device(instance, isDebugMode);
    device = O1F4Vulkan::create_logical_device(physicalDevice, surface, isDebugMode);
    std::array<vk::Queue, 2> queues = O1F4Vulkan::get_queue(physicalDevice, surface, device, isDebugMode);
    graphicsQueue = queues[0];
    presentQueue = queues[1];
    O1F4Vulkan::query_swapchain_support(physicalDevice, surface, true);
    O1F4Vulkan::SwapchainBundle bundle = O1F4Vulkan::create_swapchain(device, physicalDevice, surface, width, height, isDebugMode);
    swapchain = bundle.swapchain;
    swapchainImages = bundle.images;
    swapchainFormat = bundle.format;
    swapchainExtent = bundle.extent;
  }

  Engine::~Engine()
  {
    device.destroySwapchainKHR(swapchain);
    device.destroy();
    instance.destroySurfaceKHR(surface);

    if(isDebugMode)
    {
      instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
    }
    instance.destroy();
    glfwTerminate();
  }

}