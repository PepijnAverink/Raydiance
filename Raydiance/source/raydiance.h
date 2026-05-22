#pragma once
#define RA_DEBUG

#define RA_WINDOWS
// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$

// MISC operations
#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


// Enable vulkan
#define COMPILE_WITH_VULKAN
#if defined(COMPILE_WITH_VULKAN)
#define COMPILE_GRAPHICS_API_VK
#endif


// Enable directx12
#define COMPILE_WITH_DIRECTX12
#if defined(COMPILE_WITH_DIRECTX12)
#define COMPILE_GRAPHICS_API_DX12
#endif


//#define DEFAULT_GRAPHICS_API RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN
#define DEFAULT_GRAPHICS_API RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12