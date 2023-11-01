#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

namespace O1F4Engine
{
	namespace O1F4Render
	{
		struct GraphicsPipelineInBundle
		{
			vk::Device device;
			std::string vertexFilepath;
			vk::Extent2D swapchainExtent;
		};

		struct GraphicsPipelineOutBundle
		{

		};

		GraphicsPipelineOutBundle make_graphics_pipeline(GraphicsPipelineInBundle specification, bool debug);
	}
}

#endif
