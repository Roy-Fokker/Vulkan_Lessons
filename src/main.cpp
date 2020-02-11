#include "window.hpp"

#include <fmt/core.h>
#include <string>

auto main() -> int
{
	std::wstring cmd_line(GetCommandLine());

	using namespace vulkan_lessons;
	
	bool exit_program{false};
	uint16_t width{800},
			 height{600};
	
	window wnd({width, height}, fmt::format(L"Vulkan Lessons - {}", 1));
	wnd.set_message_callback(window::message_type::keypress, 
		[&exit_program](uintptr_t key_code, uintptr_t extension) -> bool
	{
			if (key_code == VK_ESCAPE)
			{
				exit_program = true;
			}

			return true;
	});

	wnd.show();
	while(wnd.handle() and (not exit_program))
	{
		wnd.process_messages();
	}

	return 0;
}