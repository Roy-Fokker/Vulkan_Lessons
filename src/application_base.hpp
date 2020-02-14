#pragma once

#include <Windows.h>
#include <vulkan/vulkan.hpp>

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
        void initialize_vulkan(HWND hwnd);

    private:
        vk::UniqueInstance instance;
    };
}