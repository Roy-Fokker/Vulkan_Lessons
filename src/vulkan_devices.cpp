#include "vulkan_devices.h"

#include <algorithm>
#include <cppitertools/filter.hpp>
#include <cppitertools/enumerate.hpp>
#include <optional>

using namespace vulkan_lessons;

namespace
{
	// Figure out if device support Queue of interest to us.
	// in this case GPU capable of graphics~!??
	auto get_queue_family_index(const vk::PhysicalDevice &device) -> std::optional<uint32_t>
	{
		auto family_properties = device.getQueueFamilyProperties();

		auto supports = [](const vk::QueueFamilyProperties &property)
		{
			return property.queueCount > 0
				and property.queueFlags & vk::QueueFlagBits::eGraphics;
		};

		auto family_index = std::optional<uint32_t>();
		// There must be a better way of getting the 1st element, 
		// if it exists
		for (auto [i, property] : family_properties 
								| iter::filter(supports)
								| iter::enumerate)
		{
			family_index = i;
			break;
		}

		return family_index;
	}

	auto is_device_suitable(const vk::PhysicalDevice &device) -> bool
	{
		auto queue_family_index = get_queue_family_index(device);

		return queue_family_index.has_value();
	}
}


vk_device::vk_device(const vk::Instance &instance)
{
	pick_physical_device(instance);
}

vk_device::~vk_device() = default;

void vk_device::pick_physical_device(const vk::Instance &instance)
{
	auto gpu_devices = instance.enumeratePhysicalDevices();

	if (gpu_devices.size() == 0)
	{
		throw std::runtime_error("Failed to find GPU with Vulkan Support");
	}

	// There must be a better way of getting the 1st element, 
	// if it exists
	for (auto &device : gpu_devices | iter::filter(is_device_suitable))
	{
		physical_device = device;
		break;
	}

	if (physical_device == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find suitable GPU");
	}
	
}
