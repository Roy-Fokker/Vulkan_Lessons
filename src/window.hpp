#pragma once

#include <Windows.h>
#include <string_view>
#include <memory>
#include <cstdint>
#include <functional>

namespace vulkan_lessons
{
	class window
	{
	public:
		struct size
		{
			uint16_t width;
			uint16_t height;
		};

		enum class message_type
		{
			resize,
			activate,
			keypress
		};
		static constexpr uint8_t max_message_types = 3;

		using callback_method = std::function<bool(uintptr_t, uintptr_t)>;

	public:
		window(const size &window_size, std::wstring_view title, uint16_t res_icon_id = 0);
		~window();

		void set_message_callback(message_type msg, const callback_method &callback);
		void show();
		void process_messages();

		HWND handle() const;

	private:
		struct atl_window_implementation;
		using window_impl_type = atl_window_implementation;

		std::unique_ptr<window_impl_type> window_impl;
	};
}