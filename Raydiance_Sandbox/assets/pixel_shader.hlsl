Texture2D albedoMap   : register(t0, space1); // binding = 1, descriptorSet = 1 (RMA_texture)
SamplerState sampler0 : register(s0, space2); // Often a separate sampler object is needed

struct PixelShaderInput
{
    float4 position : SV_POSITION;
    float2 texCoord : TEXCOORD0;
};


float4 main(PixelShaderInput input) : SV_TARGET0
{
    float3 color = albedoMap.Sample(sampler0, input.texCoord).rgb;
    return float4(color, 1.0);
}