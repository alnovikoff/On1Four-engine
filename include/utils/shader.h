#ifndef SHADER_H
#define SHADER_H

#include <of_pch.h>

namespace O1F4VulkanUtil {
	std::vector<char> readFile(std::string filename, bool debug);

	vk::ShaderModule createModule(std::string filename, vk::Device device, bool debug);
}

#endif // SHADER_H