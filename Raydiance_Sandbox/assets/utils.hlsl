#if defined(VULKAN)
#define CONSTANTS(name, type) [[vk::push_constant]] type name;
#elif defined(D3D12)
#define CONSTANTS(name, type) ConstantBuffer<type> name : register(b999, space999)
#endif