// HLSL equivalent for Vulkan using dxc - Vertex Shader

// Constant Buffer Declaration
// In Vulkan-style HLSL, 'register(bX, spaceY)' maps to Vulkan's 'binding = X, descriptorSet = Y'
// 'b' is for constant buffers (uniform buffers in GLSL)
#include "./utils.hlsl"

struct FrameData
{
    float4x4 viewProj;
    float4x4 model; // HLSL uses 'float4x4' for 4x4 matrices
};

CONSTANTS(frame, FrameData);


// Input structure for vertex shader
// These correspond to the vertex attributes (layout(location = X) in)
struct VertexShaderInput
{
    float3 inPosition : POSITION;  // Or TEXCOORD0, or a custom semantic like 'ATTRIB0'
    float2 inTexCoord : TEXCOORD0; // Corresponds to layout(location = 2)
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
    output.position = mul(mul(float4(input.inPosition, 1.0), frame.model), frame.viewProj);
    output.texCoord = input.inTexCoord;
    
    return output;
}