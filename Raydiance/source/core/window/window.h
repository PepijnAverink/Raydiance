#pragma once
// Descriptor include
#include "./core/window/window_descriptor.h"


// Core includes
#include "./core/error/result.h"
#include "./core/event/event.h"


//
#include <string>


// TODO:: Abstract the win32 api platform depenency
namespace Raydiance
{
	class Window
	{
	public:
		virtual ~Window();

		static Window* Create(const WindowDescriptor& _windowDescriptor);

		// Updates windows event queue and processes events
		virtual void PollEvents(void) = 0;

		// Shows window or hides main application window
		virtual void Show(void) = 0;
		virtual void Hide(void) = 0;

		// Functions to help with window closure
		virtual void Close(void) { m_Closed = true; }

		// TODO:: Replace with event system callback
		inline bool ShouldClose() const { return m_Closed; }

		// Getters for the native window handle
		virtual void* GetWindowHandlePtr() const = 0;

		// TODO:: Look into using std::string_view
		// Getter for the window title
		inline const std::string GetTitle() const { return m_Title; }

		// Getters for window dimension
		inline uint32_t GetClientWidth()  const { return m_Width; }
		inline uint32_t GetClientHeight() const { return m_Height; }

		// Event callback
		EventCallbackFn EventCallback = nullptr;
		virtual void SetEventCallback(const EventCallbackFn& _callback) { EventCallback = _callback; }

	protected:
		Window();
		Result Initialize(const WindowDescriptor& _windowDescriptor);


		// General window information
		std::string m_Title;
		uint32_t    m_Width;
		uint32_t    m_Height;

		bool m_Closed = false;
		bool m_Focussed = false; // Whether or not the window is currently in focus
	};
}