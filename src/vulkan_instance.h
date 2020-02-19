#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace vulkan_lessons
{
	class vk_instance final
	{
	public:
		vk_instance();
		~vk_instance();

	private:
		void create_instance();
		auto create_application_info()->vk::ApplicationInfo;
		auto get_required_extensions()->std::vector<const char*>;
		auto get_validation_layers()->std::vector<const char*>;

		void setup_debug_messenger();
		void delete_debug_messenger();

	private:
		vk::UniqueInstance instance;
		vk::DispatchLoaderDynamic dispatch_loader;
		vk::DebugUtilsMessengerEXT debug_messenger;
	};
}