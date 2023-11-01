#include <drivers/vulkan/vulkan_device.h>
#include <drivers/vulkan/vulkan_logging.h>
#include <drivers/vulkan/vulkan_queue_family.h>

namespace O1F4Engine
{
  namespace O1F4Render
  {
    bool checkDeviceExtensionSupport(const vk::PhysicalDevice &device, const std::vector<const char *> &requestedExtensions, const bool debug)
    {
      std::set<std::string> requiredExtensions(requestedExtensions.begin(), requestedExtensions.end());

      if (debug)
      {
        std::cout << "Device can support extensions:\n";
      }

      for (vk::ExtensionProperties extension : device.enumerateDeviceExtensionProperties())
      {
        if (debug)
        {
          std::cout << "\t\"" << extension.extensionName << "\"\n";
        }
        requiredExtensions.erase(extension.extensionName);
      }
      return requiredExtensions.empty();
    }

    bool isSuitable(const vk::PhysicalDevice &device, const bool debug)
    {
      const std::vector<const char *> requestedExtensions = {
          VK_KHR_SWAPCHAIN_EXTENSION_NAME};

      if (debug)
      {
        std::cout << "We are requesting device extensions:\n";
        for (const char *extension : requestedExtensions)
        {
          std::cout << "\t\"" << extension << "\"\n";
        }
      }

      if (bool extensionSupported = checkDeviceExtensionSupport(device, requestedExtensions, debug))
      {
        if (debug)
        {
          std::cout << "Device can support the requested extensions!\n";
        }
      }
      else
      {
        if (debug)
        {
          std::cout << "Device can't support the requested extensions!\n";
        }
        return false;
      }
      return true;
    }

    vk::PhysicalDevice choose_physical_device(vk::Instance &instance, bool debug)
    {
      std::vector<vk::PhysicalDevice> availableDevice = instance.enumeratePhysicalDevices();

      if (debug)
      {
        std::cout << "There are " << availableDevice.size() << " physical devices available on this system\n";
      }

      for (vk::PhysicalDevice device : availableDevice)
      {
        if (debug)
        {
          O1F4RenderUtils::log_device_properties(device);
        }
        if (isSuitable(device, debug))
        {
          return device;
        }
      }
      return nullptr;
    }

    vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug)
    {
      QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);
      std::vector<uint32_t> uniqueIndices;
      uniqueIndices.push_back(indices.graphicsFamily.value());
      if (indices.graphicsFamily.value() != indices.presentFamily.value())
      {
        uniqueIndices.push_back(indices.presentFamily.value());
      }

      float queuePriority = 1.0f;

      std::vector<vk::DeviceQueueCreateInfo> queueCreateInfo;
      for (uint32_t queueFamilyIndex : uniqueIndices)
      {
        queueCreateInfo.push_back(
            vk::DeviceQueueCreateInfo(
                vk::DeviceQueueCreateFlags(), queueFamilyIndex, 1, &queuePriority));
      }

      std::vector<const char *> deviceExtensions = {
          VK_KHR_SWAPCHAIN_EXTENSION_NAME};

      vk::PhysicalDeviceFeatures deviceFeatures = vk::PhysicalDeviceFeatures();

      std::vector<const char *> enabledLayers;
      if (debug)
      {
        enabledLayers.push_back("VK_LAYER_KNROHOS_validation");
      }
      vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo(
          vk::DeviceCreateFlags(),
          queueCreateInfo.size(),
          queueCreateInfo.data(),
          enabledLayers.size(),
          enabledLayers.data(),
          deviceExtensions.size(),
          deviceExtensions.data(),
          &deviceFeatures);

      try
      {
        vk::Device device = physicalDevice.createDevice(deviceInfo);
        if (debug)
        {
          std::cout << "GPU was successfully abstracted!\n";
        }
        return device;
      }
      catch (vk::SystemError err)
      {
        if (debug)
        {
          std::cout << "Device creation failed\n";
          return nullptr;
        }
      }
      return nullptr;
    }

    std::array<vk::Queue, 2> get_queue(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, vk::Device device, bool debug)
    {
      QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);

      return {
          {device.getQueue(indices.graphicsFamily.value(), 0),
          device.getQueue(indices.presentFamily.value(), 0)}};
    }
  }
}