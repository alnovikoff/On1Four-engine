#ifndef RENDERER_H
#define RENDERER_H

// #include <core/defines.h>
#include <of_pch.h>

#include <drivers/vulkan/vulkan_frame.h>

namespace O1F4Engine
{
  namespace O1F4Render
  {
    class Renderer
    {
  public:
      Renderer(GLFWwindow *window, int width, int height, bool isDebug); // Corrected here
      ~Renderer();

      // Instance setup
      void make_render_instance(GLFWwindow *window, bool isDebug);

      // Device setup
      void make_device(int width, int height, bool isDebug);

      // Debug messenger
      void make_debug_messenger(bool isDebug);

      void make_pipeline(bool isDebug);

  private:
      vk::Instance instance{nullptr};

      // Debug callback
      vk::DebugUtilsMessengerEXT debugMessenger{nullptr};

      // Dynamic instance dispatcher
      vk::DispatchLoaderDynamic dldi;
      vk::SurfaceKHR surface;

      // Device - related variable
      vk::PhysicalDevice physicalDevice{nullptr};
      vk::Device device{nullptr};
      vk::Queue graphicsQueue{nullptr};
      vk::Queue presentQueue{nullptr};
      vk::SwapchainKHR swapchain;
      std::vector<O1F4Engine::O1F4Render::SwapchainFrame> swapchainFrames;
      vk::Format swapchainFormat;
      vk::Extent2D swapchainExtent;
    };
  }
}
#endif // RENDERER_H