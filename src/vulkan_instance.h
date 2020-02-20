#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace vulkan_lessons
{
	class vk_instance final
	{
	public:
		vk_instance(HWND hWnd);
		~vk_instance();

		auto get_instance() const -> const vk::Instance &;
		auto get_surface() const -> const vk::SurfaceKHR &;

	private:
		void create_instance();
		auto create_application_info()->vk::ApplicationInfo;
		auto get_required_extensions()->std::vector<const char*>;
		auto get_validation_layers()->std::vector<const char*>;

		void setup_debug_messenger();
		void delete_debug_messenger();

		void create_surface(HWND hWnd);

	private:
		vk::UniqueInstance instance;
		vk::DispatchLoaderDynamic dispatch_loader;
		vk::DebugUtilsMessengerEXT debug_messenger;
		vk::UniqueSurfaceKHR surface;
	};
}