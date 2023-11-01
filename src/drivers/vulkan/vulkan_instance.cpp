#include <drivers/vulkan/vulkan_instance.h>

namespace O1F4Engine
{
  namespace O1F4Render
  {
    bool supported(std::vector<const char *> &extensions, std::vector<const char *> &layers, bool debug)
    {
      bool found;

      // Checking extensions support
      std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

      if (debug)
      {
        std::cout << "\nDevice van support following extensions:\n";
        for (vk::ExtensionProperties supportedExtension : supportedExtensions)
        {
          std::cout << '\t' << supportedExtension.extensionName << '\n';
        }
      }

      for (const char *extension : extensions)
      {
        found = false;
        for (vk::ExtensionProperties supportedExtension : supportedExtensions)
        {
          if (strcmp(extension, supportedExtension.extensionName) == 0)
          {
            found = true;
            if (debug)
            {
              std::cout << "Extension \"" << extension << "\" is supported!\n";
            }
          }
        }
        if (!found)
        {
          if (debug)
          {
            std::cout << "Extension \"" << extension << "\" is NOT supported!\n";
          }
          return false;
        }
      }

      // Checking layers support
      std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();

      if (debug)
      {
        std::cout << "\nDevice can support the following layers:\n";
        for (vk::LayerProperties supportedLayer : supportedLayers)
        {
          std::cout << '\t' << supportedLayer.layerName << '\n';
        }
      }

      for (const char *layer : layers)
      {
        found = false;
        for (vk::LayerProperties supportedLayer : supportedLayers)
        {
          if (strcmp(layer, supportedLayer.layerName) == 0)
          {
            found = true;
            if (debug)
            {
              std::cout << "Layer \"" << layer << "\" is supported!\n";
            }
          }
        }
        if (!found)
        {
          if (debug)
          {
            std::cout << "Layer\"" << layer << "\" is NOT supported!\n";
          }
          return false;
        }
      }

      return true;
    }

    vk::Instance create_vulkan_instance(bool debug, const char *application_name)
    {
      uint32_t version{0};
      vkEnumerateInstanceVersion(&version);
      if (debug)
      {
        std::cout << "System can support vulkan variant: " << VK_API_VERSION_VARIANT(version)
                  << "\nMajor: " << VK_API_VERSION_MAJOR(version)
                  << "\nMinor: " << VK_API_VERSION_MINOR(version)
                  << "\nPatch: " << VK_API_VERSION_PATCH(version) << '\n';
      }

      // Remove lower 12 bytes
      version &= ~(0xFFFU);

      // Dropdown to earlier version
      version = VK_MAKE_API_VERSION(0, 1, 0, 0);

      // Application info
      vk::ApplicationInfo appInfo = vk::ApplicationInfo(
          application_name,
          version,
          application_name,
          version,
          version);

      // Query which extensions glfw need in order to interface with vulkan
      uint32_t glfwExtensionCount = 0;
      const char **glfwExtensions;
      glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

      std::vector<const char *> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
      if (debug)
      {
        extensions.push_back("VK_EXT_debug_utils");
      }

      if (debug)
      {
        std::cout << "Extenstions to be requested: \n";

        for (const char *extensionName : extensions)
        {
          std::cout << "\t\"" << extensionName << "\"\n";
        }
      }

      std::vector<const char *> layers;
      if (debug)
      {
        layers.push_back("VK_LAYER_KHRONOS_validation");
      }
      
      if (!supported(extensions, layers, debug))
      {
        return nullptr;
      }

      vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
          vk::InstanceCreateFlags(),
          &appInfo,
          static_cast<uint32_t>(layers.size()), layers.data(),
          static_cast<uint32_t>(extensions.size()), extensions.data());

      try
      {
        return vk::createInstance(createInfo, nullptr);
      }
      catch (vk::SystemError e)
      {
        if (debug)
        {
          std::cout << "failed to create Instance! vk::createInstance(createInfo, nullptr)\n";
        }
        return nullptr;
      }
    }
  }
}