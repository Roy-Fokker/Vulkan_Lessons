#include "vulkan_instance.h"

#include <cstring>

using namespace vulkan_lessons;

namespace
{
    auto cstr_cmp_less(const char* a, const char* b) -> bool
    {
        return std::strcmp(a, b) < 0;
    }
}

vk_instance::vk_instance()
{
	create_instance();
}

vk_instance::~vk_instance() = default;

void vk_instance::create_instance()
{
	auto app_info = create_application_info();
	auto extensions = get_required_extensions();
	auto layers = get_validation_layers();

	auto instance_info = vk::InstanceCreateInfo()
		.setPApplicationInfo(&app_info)
		.setEnabledExtensionCount(static_cast<uint32_t>(extensions.size()))
		.setPpEnabledExtensionNames(extensions.data())
		.setEnabledLayerCount(static_cast<uint32_t>(layers.size()))
		.setPpEnabledLayerNames(layers.data());

	instance = vk::createInstanceUnique(instance_info);
}

auto vk_instance::create_application_info() -> vk::ApplicationInfo
{
	return vk::ApplicationInfo()
		.setPApplicationName("Vulkan Lessons")
		.setApplicationVersion(VK_MAKE_VERSION(0, 1, 0))
		.setPEngineName("No Engine")
		.setEngineVersion(VK_MAKE_VERSION(0, 1, 0))
		.setApiVersion(VK_API_VERSION_1_2);
}

auto vk_instance::get_required_extensions() -> std::vector<const char*>
{
	// What extensions do we want?
	auto desired_extensions = std::vector{
		VK_KHR_SURFACE_EXTENSION_NAME,
		VK_KHR_WIN32_SURFACE_EXTENSION_NAME, // Not sure if this is required??
#ifdef DEBUG
	VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
	VK_EXT_DEBUG_UTILS_EXTENSION_NAME
#endif // DEBUG
	};
	std::sort(desired_extensions.begin(), desired_extensions.end(),
				cstr_cmp_less);

	// checking extension support
	auto extensions = vk::enumerateInstanceExtensionProperties();
	std::sort(extensions.begin(), extensions.end(),
				[](vk::ExtensionProperties const& a, vk::ExtensionProperties const& b)
	{
		return cstr_cmp_less(a.extensionName, b.extensionName);
	});

	// Get only the extension names
	auto available_extensions = std::vector<const char*>{};
	for (auto& ext : extensions)
	{
		available_extensions.emplace_back(ext.extensionName);
	}

	// Does this machine support the extensions?
	auto are_extensions_found = std::includes(available_extensions.begin(), available_extensions.end(),
												desired_extensions.begin(), desired_extensions.end(),
												cstr_cmp_less);
	if (not are_extensions_found)
	{
		return {};
	}

	return desired_extensions;
}

auto vk_instance::get_validation_layers() -> std::vector<const char*>
{
	// Don't enable validation layers if we are not debugging.
#ifndef DEBUG
	return {};
#endif

	// What debug layers do we want to see?
	auto desired_validation_layers = std::vector{
		"VK_LAYER_LUNARG_standard_validation"
	};
	std::sort(desired_validation_layers.begin(), desired_validation_layers.end(),
			  cstr_cmp_less);

	// checking layer support
	auto validation_layers = vk::enumerateInstanceLayerProperties();
	std::sort(validation_layers.begin(), validation_layers.end(),
			  [](vk::LayerProperties const& a, vk::LayerProperties const& b)
	{
		return cstr_cmp_less(a.layerName, b.layerName);
	});

	// Get only the layer names
	auto available_layers = std::vector<const char*>{};
	for (auto& layer : validation_layers)
	{
		available_layers.emplace_back(layer.layerName);
	}

	// Does machine support desired layers
	auto are_layers_found = std::includes(available_layers.begin(), available_layers.end(),
										  desired_validation_layers.begin(), desired_validation_layers.end(),
										  cstr_cmp_less);

	if (not are_layers_found)
	{
		return {};
	}

	return desired_validation_layers;
}
