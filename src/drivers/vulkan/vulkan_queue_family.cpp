#include <drivers/vulkan/vulkan_queue_family.h>

namespace O1F4VulkanUtil
{
	QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug)
  {
    QueueFamilyIndices indices;

    std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

    if (debug)
    {
      std::cout << "System can support " << queueFamilies.size() << " queueFamilies\n";
    }

    int i = 0;
    for (vk::QueueFamilyProperties queueFamily : queueFamilies)
    {
      if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
      {
        indices.graphicsFamily = i;
        if (debug)
        {
          std::cout << "Queue family " << i << " is suitable for graphics\n";
        }
      }

      if (device.getSurfaceSupportKHR(i, surface))
      {
        indices.presentFamily = i;
        if (debug)
        {
          std::cout << "Queue family " << i << " is suitable for presenting\n";
        }
      }

      if (indices.isComplete())
      {
        break;
      }
      i++;
    }
    return indices;
  }
}