#include "window.h"

#include <Windows.h>
#include <fmt/core.h>

#ifdef _DEBUG
// CRT Memory Leak detection
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#endif


auto main() -> int
{
#ifdef _DEBUG
	// Detects memory leaks upon program exit
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	using namespace Win32;

	bool exit_application{ false };

	auto wnd = window(L"Vulkan Lessons", { 800, 600 });
	wnd.on_message(window::message_name::keypress, [&](uintptr_t key_code, uintptr_t extension) -> bool
	{
		switch (key_code)
		{
		case VK_ESCAPE:
			exit_application = true;
			break;
		}
		return true;
	});

	wnd.show();
	while (wnd.handle() and not exit_application)
	{
		wnd.process_messages();
	}

	return 0;
}
