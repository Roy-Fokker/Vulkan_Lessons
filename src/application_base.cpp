#include "application_base.hpp"

#include <algorithm>
#include <string>
#include <cppitertools/enumerate.hpp>

using namespace vulkan_lessons;

namespace 
{
    bool cstr_cmp_less(const char *a, const char *b)
    {
        return strcmp(a, b) < 0;
    }
}

application_base::application_base(HWND hwnd)
{
    create_vulkan_instance();
    
}

application_base::~application_base() = default;

void application_base::update()
{

}

void application_base::create_vulkan_instance()
{
    // initialize the vk::ApplicationInfo structure
    auto app_info = vk::ApplicationInfo(
        "Vulkan Lessons", 1, // Dummy name
        "No Engine", 1,      // Dummny name
        VK_API_VERSION_1_2
    );

    // get supported extensions
    auto extension_names = get_supported_extensions();

    // get validation layers
    auto validation_layers = get_validation_layers();

    // initialize the vk::InstanceCreateInfo
    auto instance_info = vk::InstanceCreateInfo()
                            .setPApplicationInfo(&app_info)
                            .setEnabledExtensionCount(static_cast<uint32_t>(extension_names.size()))
                            .setPpEnabledExtensionNames(extension_names.data())
                            .setEnabledLayerCount(static_cast<uint32_t>(validation_layers.size()))
                            .setPpEnabledLayerNames(validation_layers.data());

    // create a UniqueInstance
    instance = vk::createInstanceUnique(instance_info);
}

auto application_base::get_supported_extensions() -> std::vector<const char *>
{
    auto desired_extensions = std::vector{
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    };
#ifdef DEBUG
    desired_extensions.insert(desired_extensions.end(), {
        VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME
    });
#endif
    std::sort(desired_extensions.begin(), desired_extensions.end(),
              cstr_cmp_less);

    // checking extension support
    auto extensions = vk::enumerateInstanceExtensionProperties();
    std::sort(extensions.begin(), extensions.end(), 
              [] (vk::ExtensionProperties const &a, vk::ExtensionProperties const &b)
    {
        return cstr_cmp_less(a.extensionName, b.extensionName);
    });

    // Get only the extension names
    auto available_extensions = std::vector<const char *>{};
    for (auto &ext : extensions)
    {
        available_extensions.emplace_back(ext.extensionName);
    }

    auto are_extensions_found = std::includes(available_extensions.begin(), available_extensions.end(),
                                              desired_extensions.begin(), desired_extensions.end(),
                                              cstr_cmp_less);
    if (not are_extensions_found)
    {
        return {};
    }

    return desired_extensions;
}

auto application_base::get_validation_layers() -> std::vector<const char *>
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
              [] (vk::LayerProperties const &a, vk::LayerProperties const &b)
    {
        return cstr_cmp_less(a.layerName, b.layerName);
    });

    // Get only the layer names
    auto available_layers = std::vector<const char *>{};
    for (auto &layer : validation_layers)
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
