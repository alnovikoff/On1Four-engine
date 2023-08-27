#include <drivers/vulkan/vulkan_device.h>

#include <drivers/vulkan/vulkan_logging.h>

namespace O1F4Vulkan
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
        log_device_properties(device);
      }
      if (isSuitable(device, debug))
      {
        return device;
      }
    }
    return nullptr;
  }

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

  SwapchainSupportDetails query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug)
  {
    SwapchainSupportDetails support;

    support.capabilities = device.getSurfaceCapabilitiesKHR(surface);

    if (debug)
    {
      std::cout << "\nSwapchain cn support the following surface capabilities: \n";

      std::cout << "\tminimum image count: " << support.capabilities.minImageCount << '\n';
      std::cout << "\tmaximum image count: " << support.capabilities.maxImageCount << '\n';

      std::cout << "\tcurrent extent: \n";
      std::cout << "\t\twidth: " << support.capabilities.currentExtent.width << '\n';
      std::cout << "\t\theight: " << support.capabilities.currentExtent.height << '\n';

      std::cout << "\tminimum supported extent: \n";
      std::cout << "\t\twidth: " << support.capabilities.minImageExtent.width << '\n';
      std::cout << "\t\theight: " << support.capabilities.minImageExtent.height << '\n';

      std::cout << "\tmaximum supported extent: \n";
      std::cout << "\t\twidth: " << support.capabilities.maxImageExtent.width << '\n';
      std::cout << "\t\theight: " << support.capabilities.maxImageExtent.height << '\n';

      std::cout << "\tmaximum image array layers: " << support.capabilities.maxImageArrayLayers << '\n';

      std::cout << "\tsupported transforms:\n";
      std::vector<std::string> stringList = log_transform_bits(support.capabilities.supportedTransforms);
      for (std::string line : stringList)
      {
        std::cout << "\t\t" << line << '\n';
      }

      std::cout << "\tcurrent transforms:\n";
      stringList = log_transform_bits(support.capabilities.currentTransform);
      for (std::string line : stringList)
      {
        std::cout << "\t\t" << line << '\n';
      }

      std::cout << "\tcurrent transforms:\n";
      stringList = log_image_usage_bits(support.capabilities.supportedUsageFlags);
      for (std::string line : stringList)
      {
        std::cout << "\t\t" << line << '\n';
      }
    }

    support.formats = device.getSurfaceFormatsKHR(surface);

    if (debug)
    {
      for (vk::SurfaceFormatKHR supportedFormat : support.formats)
      {
        std::cout << "supported pixel format: " << vk::to_string(supportedFormat.format) << '\n';
        std::cout << "supported color space: " << vk::to_string(supportedFormat.colorSpace) << '\n';
      }
    }

    support.presentModes = device.getSurfacePresentModesKHR(surface);
    for (vk::PresentModeKHR presentMode : support.presentModes)
    {
      std::cout << '\t' << log_present_mode(presentMode) << '\n';
    }
    return support;
  }

  vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats)
  {
    for (vk::SurfaceFormatKHR format : formats)
    {
      if (format.format == vk::Format::eB8G8R8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
      {
        return format;
      }
    }
    return formats[0];
  }
  // Mobilde device refresh at 1000 frames pres sec is not necessary
  vk::PresentModeKHR choose_swapchain_present_mode(std::vector<vk::PresentModeKHR> presentModes)
  {
    for (vk::PresentModeKHR presentMode : presentModes)
    {
      if (presentMode == vk::PresentModeKHR::eMailbox)
      {
        return presentMode;
      }
    }
    return vk::PresentModeKHR::eFifo;
  }

  vk::Extent2D choose_spwapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities)
  {
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
      return capabilities.currentExtent;
    }
    else
    {
      vk::Extent2D extent = {width, height};

      extent.width = std::min(
          capabilities.maxImageExtent.width,
          std::max(capabilities.minImageExtent.width, width));

      extent.height = std::min(
          capabilities.maxImageExtent.height,
          std::max(capabilities.minImageExtent.height, height));

      return extent;
    }
  }

  SwapchainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height, bool debug)
  {
    SwapchainSupportDetails support = query_swapchain_support(physicalDevice, surface, debug);

    vk::SurfaceFormatKHR format = choose_swapchain_surface_format(support.formats);

    vk::PresentModeKHR presentMode = choose_swapchain_present_mode(support.presentModes);

    vk::Extent2D extent = choose_spwapchain_extent(width, height, support.capabilities);

    uint32_t imageCount = std::min(
        support.capabilities.maxImageCount,
        support.capabilities.minImageCount + 1);

    vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR(
        vk::SwapchainCreateFlagsKHR(), surface, imageCount, format.format, format.colorSpace,
        extent, 1, vk::ImageUsageFlagBits::eColorAttachment);

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if(indices.graphicsFamily.value() != indices.presentFamily.value())
    {
      createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
      createInfo.queueFamilyIndexCount = 2;
      createInfo.pQueueFamilyIndices = queueFamilyIndices;
    }
    else
    {
      createInfo.imageSharingMode = vk::SharingMode::eExclusive;
    }

    createInfo.preTransform = support.capabilities.currentTransform;
    createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

    SwapchainBundle bundle{};
    try {
      bundle.swapchain = logicalDevice.createSwapchainKHR(createInfo);
    }
    catch(vk::SystemError err)
    {
      throw std::runtime_error("failed to create swapchain!");
    }

    bundle.images = logicalDevice.getSwapchainImagesKHR(bundle.swapchain);
    bundle.format = format.format;
    bundle.extent = extent;

    return bundle;
  }
}