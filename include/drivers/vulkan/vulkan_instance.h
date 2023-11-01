#ifndef VULKAN_INSTANCE_H
#define VULKAN_INSTANCE_H

#include <of_pch.h>

namespace O1F4Engine
{
  namespace O1F4Render
  {
    bool supported(std::vector<const char *> &extensions, std::vector<const char *> &layers, bool debug);

    vk::Instance create_vulkan_instance(bool debug, const char *application_name);
  }
}

#endif // VULKAN_INSTANCE_H