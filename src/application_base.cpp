#include "application_base.hpp"

#include <algorithm>
#include <string>
#include <cppitertools/enumerate.hpp>

using namespace vulkan_lessons;

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
    // checking extension support
    auto extensions = vk::enumerateInstanceExtensionProperties();

    return {};
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
              [](const char *a, const char *b)
    {
        return strcmp(a, b) < 0;
    });

    // checking layer support
    auto validation_layers = vk::enumerateInstanceLayerProperties();
    std::sort(validation_layers.begin(), validation_layers.end(), 
              [] (vk::LayerProperties const &a, vk::LayerProperties const &b)
    {
        return strcmp(a.layerName, b.layerName) < 0;
    });

    auto available_layers = std::vector<const char *>{};
    for (auto &layer : validation_layers)
    {
        available_layers.emplace_back(layer.layerName);
    }

    auto comp = [](const char *a, const char *b)
    {
        return strcmp(a, b) == 0;
    };

    auto are_layers_found = std::includes(available_layers.begin(), available_layers.end(),
                                          desired_validation_layers.begin(), desired_validation_layers.end(),
                                          comp);

    if (not are_layers_found)
    {
        return {};
    }

    return desired_validation_layers;
}

void application_base::check_validation_layer_support()
{

}