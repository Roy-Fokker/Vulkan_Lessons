#include "application_base.hpp"

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
        "Vulkan Lessons", 1, 
        "No Engine", 1, 
        VK_API_VERSION_1_2
    );

    // initialize the vk::InstanceCreateInfo
    auto instance_info = vk::InstanceCreateInfo({}, &app_info);

    // create a UniqueInstance
    instance = vk::createInstanceUnique(instance_info);
}
