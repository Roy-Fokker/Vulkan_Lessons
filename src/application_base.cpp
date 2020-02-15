#include "application_base.hpp"

#include <algorithm>
#include <vector>

using namespace vulkan_lessons;

application_base::application_base(HWND hwnd)
{
    initialize_vulkan(hwnd);
}

application_base::~application_base() = default;

void application_base::update()
{

}

void application_base::initialize_vulkan(HWND hwnd)
{
    // initialize the vk::ApplicationInfo structure
    auto app_info = vk::ApplicationInfo(
        "Vulkan Lessons", 1, // Dummy name
        "No Engine", 1,      // Dummny name
        VK_API_VERSION_1_2
    );

    // checking extension support
    auto extensions = vk::enumerateInstanceExtensionProperties();
    std::sort(extensions.begin(), extensions.end(), 
              [] (vk::ExtensionProperties const &a, vk::ExtensionProperties const &b)
    {
        return strcmp(a.extensionName, b.extensionName) < 0;
    });

    // initialize the vk::InstanceCreateInfo
    auto instance_info = vk::InstanceCreateInfo({}, &app_info);

    // create a UniqueInstance
    instance = vk::createInstanceUnique(instance_info);
}
