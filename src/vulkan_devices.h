#pragma once

#include <vulkan/vulkan.hpp>

namespace vulkan_lessons
{
	class vk_device final
	{
	public:
		vk_device(const vk::Instance &instance);
		~vk_device();

	private:
		void pick_physical_device(const vk::Instance &instance);

	private:
		vk::PhysicalDevice physical_device;
	};
}