#include <drivers/vulkan/vulkan_device.h>

#include <drivers/vulkan/vulkan_logging.h>

namespace O1F4Vulkan
{
	bool checkDeviceExtensionSupport(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool debug)
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

	bool isSuitable(const vk::PhysicalDevice& device, const bool debug)
	{
		const std::vector<const char*> requestedExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		if(debug)
		{
			std::cout << "We are requesting device extensions:\n";
			for(const char* extension : requestedExtensions)
			{
				std::cout << "\t\"" << extension << "\"\n";
			}
		}

		if(bool extensionSupported = checkDeviceExtensionSupport(device, requestedExtensions, debug))
		{
			if(debug)
			{
				std::cout << "Device can support the requested extensions!\n";
			}
		}
		else
		{
			if(debug)
			{
				std::cout << "Device can't support the requested extensions!\n";
			}
			return false;
		}
		return true;
	}

	vk::PhysicalDevice choose_physical_device(vk::Instance& instance, bool debug)
	{
		std::vector<vk::PhysicalDevice> availableDevice = instance.enumeratePhysicalDevices();

		if(debug)
		{
			std::cout << "There are " << availableDevice.size() << " physical devices available on this system\n";
		}

		for(vk::PhysicalDevice device : availableDevice)
		{
			if(debug)
			{
				log_device_properties(device);
			}
			if(isSuitable(device, debug))
			{
			 	return device;
			}
		}
		return nullptr;
	}

	QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, bool debug)
	{
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

		if(debug)
		{
			std::cout << "System can support " << queueFamilies.size() << " queueFamilies\n";
		}

		int i = 0;
		for(vk::QueueFamilyProperties queueFamily : queueFamilies)
		{
			if(queueFamily.queueFlags & vk::QueueFlagBits::eGraphics)
			{
				indices.graphicsFamily = i;
				indices.presentFamily = i;
				if(debug)
				{
					std::cout << "Queue family " << i << " is suitable for graphics and presenting\n";
				}
			}

			if(indices.isComplete())
			{
				break;
			}
			i++;
		}
		return indices;
	}
}