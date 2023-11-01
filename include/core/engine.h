#ifndef ENGINE_H
#define ENGINE_H

#include <core/defines.h>
#include <of_pch.h>

#include <core/window.h>
#include <graphics/renderer.h>

#include <drivers/vulkan/vulkan_frame.h>


namespace O1F4Engine
{
  class ON1F_API Engine
  {
public:
    Engine();

    ~Engine();

private:
    bool isDebugMode = true;

    O1F4PAL::Window* main_window;
    O1F4Render::Renderer* main_renderer;
  };
} // namespace O1F4Engine
#endif // ENGINE_H
