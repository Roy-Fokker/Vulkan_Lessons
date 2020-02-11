#pragma once

#include <Windows.h>

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
        void initialize_vulkan();

    private:
        
    };
}