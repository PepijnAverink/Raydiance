#include "./pch.h"
#include "./core/window/window.h"

// Windows
#include "./platform/win/core/window/win_window.h"

namespace Raydiance
{
	Window::Window()
	{ }

	Window::~Window()
	{ }

	Window* Window::Create(const WindowDescriptor& _windowDescriptor)
	{
		// Windows
		Win_Window* win = new Win_Window();
		win->Initialize(_windowDescriptor);

		return win;
	}

	Result Window::Initialize(const WindowDescriptor& _windowDescriptor)
	{
		m_Title  = _windowDescriptor.Title;

		m_Width  = _windowDescriptor.Width;
		m_Height = _windowDescriptor.Height;

		return Result::RESULT_GOOD;
	}
}
