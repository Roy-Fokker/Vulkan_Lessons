#pragma once

#include <Windows.h>
#include <vulkan/vulkan.hpp>
#include <vector>

namespace vulkan_lessons
{
    class application_base
    {
    public:
        application_base() = delete;
        application_base(HWND hwnd);
        ~application_base();

        void update();

    private:
        void create_vulkan_instance();
        auto get_supported_extensions() -> std::vector<const char *>;
        auto get_validation_layers() -> std::vector<const char *>;

    private:
        vk::UniqueInstance instance;
    };
}