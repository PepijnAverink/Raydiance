#pragma once
// Parant class include
#include "./core/window/window.h"

// Windows includes
#include <windows.h>

namespace Raydiance
{
	class Win_Window final : public Window
	{
	public:
		         Win_Window();
		virtual ~Win_Window();
		
		Result Initialize(const WindowDescriptor& _windowDescriptor);


		// Updates windows event queue and processes events
		virtual void PollEvents(void) override;

		// Shows window or hides main application window
		virtual void Show(void) override;
		virtual void Hide(void) override;

		// Getters for the native window handle
		virtual void* GetWindowHandlePtr() const override;

	private:
		// Main window handle used to reference the window in various API's
		HWND m_WindowHandle;
	};
}