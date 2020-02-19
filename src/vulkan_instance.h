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

	private:
		vk::UniqueInstance instance;
	};
}