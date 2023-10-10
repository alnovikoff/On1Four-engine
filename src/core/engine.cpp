#include <core/engine.h>
#include <core/window.h>

#include <drivers/vulkan/vulkan_instance.h>
#include <drivers/vulkan/vulkan_logging.h>
#include <drivers/vulkan/vulkan_device.h>
#include <drivers/vulkan/vulkan_swapchain.h>
#include <graphics/vulkan/vulkan_pipeline.h>

namespace O1F4Engine
{
  Engine::Engine()
  {
    main_window = new Window(800, 600, "Window Title", isDebugMode);
    main_renderer = new Renderer(main_window->get_window(), 800, 600, isDebugMode);

  }

  Engine::~Engine()
  {

  }

}