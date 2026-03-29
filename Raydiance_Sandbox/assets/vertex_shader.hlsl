// HLSL equivalent for Vulkan using dxc - Vertex Shader

// Constant Buffer Declaration
// In Vulkan-style HLSL, 'register(bX, spaceY)' maps to Vulkan's 'binding = X, descriptorSet = Y'
// 'b' is for constant buffers (uniform buffers in GLSL)
#if defined(VULKAN)
#define CONSTANTS(name, type) [[vk::push_constant]] type name;
#elif defined(D3D12)
#define CONSTANTS(name, type) ConstantBuffer<type> name : register(b999, space999)
#endif

struct FrameData
{
    float4x4 view;
	float4x4 proj;
    float4x4 model; // HLSL uses 'float4x4' for 4x4 matrices
};

CONSTANTS(frame, FrameData);

// Input structure for vertex shader
// These correspond to the vertex attributes (layout(location = X) in)
struct VertexShaderInput
{
    float3 inPosition   : POSITION;    // Or TEXCOORD0, or a custom semantic like 'ATTRIB0'
    float2 inTexCoord   : TEXCOORD0;   // Corresponds to layout(location = 2)
};

struct PixelShaderInput
{
    float4 position : SV_POSITION; // gl_Position in GLSL
    float2 texCoord : TEXCOORD0;
};

// Main vertex shader function
PixelShaderInput main(VertexShaderInput input)
{
    PixelShaderInput output;
    
    output.position = mul(mul(mul(float4(input.inPosition, 1.0), frame.model), frame.view), frame.proj);
    //output.position = mul(proj, mul(view, mul(model, float4(input.inPosition, 1.0))));
    output.texCoord = input.inTexCoord;
    
    return output;
}