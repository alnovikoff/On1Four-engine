#ifndef ENGINE_H
#define ENGINE_H

#include <core/defines.h>
#include <of_pch.h>

namespace O1F4Engine
{
  class ON1F_API Engine
  {
public:
    Engine();

    ~Engine();

private:
    // Debug activation
    bool isDebugMode = true;

    int width{640};
    int height{480};
    GLFWwindow *window{nullptr};

    // Vulkan instance
    vk::Instance instance{nullptr};

    // Debug callback
    vk::DebugUtilsMessengerEXT debugMessenger{nullptr};

    // Dynamic instance dispatcher
    vk::DispatchLoaderDynamic dldi;

    // Device - related variable
    vk::PhysicalDevice physicalDevice{nullptr};

    void build_glfw_window();

    // Instance setup
    void make_instance();

    // Device setup
    void make_device();

    // Debug messenger
    void make_debug_messenger();
  };
} // namespace O1F4Engine
#endif // ENGINE_H
