#pragma once
#define RA_DEBUG

#define RA_WINDOWS
// ^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$

// MISC operations
#define BIT(x) (1 << x)
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)


#define DEFAULT_GRAPHICS_API RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN