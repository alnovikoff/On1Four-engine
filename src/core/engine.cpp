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
    
    make_debug_messenger();

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
  }

  void Engine::make_device() 
  {
    physicalDevice = O1F4Vulkan::choose_physical_device(instance, isDebugMode);
    O1F4Vulkan::findQueueFamilies(physicalDevice, isDebugMode);
  }

  void Engine::make_debug_messenger()
  {
    debugMessenger = O1F4Vulkan::make_debug_messenger(instance, dldi);
  }

  Engine::~Engine()
  {
    instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
    instance.destroy();
    glfwTerminate();
  }

}