#pragma once

#include "vulkan_instance.h"
#include <vulkan/vulkan.hpp>

namespace vulkan_lessons
{
	class vk_device final
	{
	public:
		vk_device(const vk_instance &instance);
		~vk_device();

	private:
		void pick_physical_device(const vk_instance &instance);
		void create_logical_device(const vk_instance &instance);

	private:
		vk::PhysicalDevice physical_device;
		vk::UniqueDevice logical_device;
		vk::Queue graphics_queue;
	};
}