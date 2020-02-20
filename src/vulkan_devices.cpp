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
	auto get_queue_family_index(const vk_instance &instance, const vk::PhysicalDevice &device) -> std::optional<uint32_t>
	{
		auto family_properties = device.getQueueFamilyProperties();

		auto supports = [&](std::pair<uint64_t, vk::QueueFamilyProperties &> &elem)
		{
			auto [i, property] = elem;
			return property.queueCount > 0
				and property.queueFlags & vk::QueueFlagBits::eGraphics
				and device.getSurfaceSupportKHR(static_cast<uint32_t>(i), instance.get_surface());
		};

		auto v = family_properties 
			   | iter::enumerate 
			   | iter::filter(supports);

		// Did we find supported queue index?
		if (v.begin() == v.end())
		{
			// Nope, didn't find it.
			return {};
		}

		return static_cast<uint32_t>(std::get<0>(*v.begin()));
	}
}

vk_device::vk_device(const vk_instance &instance)
{
	pick_physical_device(instance);
	create_logical_device(instance);
}

vk_device::~vk_device() = default;

void vk_device::pick_physical_device(const vk_instance &instance)
{
	auto gpu_devices = instance.get_instance().enumeratePhysicalDevices();

	if (gpu_devices.size() == 0)
	{
		throw std::runtime_error("Failed to find GPU with Vulkan Support");
	}

	auto is_device_suitable = [&](const vk::PhysicalDevice &device) -> bool
	{
		auto queue_family_index = get_queue_family_index(instance, device);

		return queue_family_index.has_value();
	};

	auto v = gpu_devices | iter::filter(is_device_suitable);
	if (v.begin() != v.end())
	{
		physical_device = *v.begin();
	}

	if (physical_device == VK_NULL_HANDLE)
	{
		throw std::runtime_error("Failed to find suitable GPU");
	}
}

void vk_device::create_logical_device(const vk_instance &instance)
{
	auto queue_priority{ 1.0f };
	auto queue_family_index = get_queue_family_index(instance, physical_device);
	auto device_queue_info = vk::DeviceQueueCreateInfo()
		.setQueueFamilyIndex(queue_family_index.value())
		.setQueueCount(1)
		.setPQueuePriorities(&queue_priority);
	
	auto device_features = vk::PhysicalDeviceFeatures{};
	auto device_info = vk::DeviceCreateInfo()
		.setQueueCreateInfoCount(1)
		.setPQueueCreateInfos(&device_queue_info)
		.setPEnabledFeatures(&device_features);

	logical_device = physical_device.createDeviceUnique(device_info);
	graphics_queue = logical_device->getQueue(queue_family_index.value(), queue_family_index.value());
	// Do i need a second queue????
}
