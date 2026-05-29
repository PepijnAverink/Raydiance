#include "./pch.h"
#include "./graphics/RHI/resource/shader/compiler/DXC/RHI_DXC_shader_compiler.h"


// Graphics includes
#include "./graphics/RHI_api/RHI_graphics_api.h"
#include "./graphics/RHI/pipeline/layout/RHI_vertex_layout.h"


// Utility includes
#include "./util/string_util.h"


// D3D12 include
#if defined(COMPILE_GRAPHICS_API_DX12)
#include <D3D12shader.h>
#include "./graphics/RHI_api/dx12/resource/RHI_DX12_resource_format.h"
#endif


// Vulkan include
#if defined(COMPILE_GRAPHICS_API_VK)
#include "./spirv_reflect.h"
#endif


namespace Raydiance
{
	namespace Graphics
	{
		RHI_DXC_ShaderCompiler::RHI_DXC_ShaderCompiler(void)
		{
			HRESULT hres;
			// Initialize DXC library
			hres = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&m_Library));
			if (FAILED(hres)) {
				throw std::runtime_error("Could not init DXC Library");
			}

			// Initialize DXC compiler
			hres = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&m_Compiler));
			if (FAILED(hres)) {
				throw std::runtime_error("Could not init DXC Compiler");
			}

			// Initialize DXC utility
			hres = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&m_Utils));
			if (FAILED(hres)) {
				throw std::runtime_error("Could not init DXC Utiliy");
			}
		}


		RHI_DXC_ShaderCompiler::~RHI_DXC_ShaderCompiler(void)
		{
			m_Utils->Release();
			m_Compiler->Release();
			m_Library->Release();
		}


		RHI_ShaderCompileResult RHI_DXC_ShaderCompiler::Compile(const RHI_ShaderCompileDescriptor* _shaderDescriptor)
		{
			// Function result
			RHI_ShaderCompileResult result{};
			result.CompilationResult = Result::RESULT_GOOD;


			// Convert strings once (avoid dangling pointers)
			//std::wstring filePath   = StringToWString(_shaderDescriptor->FilePath.GetPath());
			//std::wstring directory  = StringToWString(_shaderDescriptor->FilePath.GetDirectory());
			std::wstring entryPoint = StringToWString(_shaderDescriptor->EntryPoint);


			IDxcBlobEncoding* sourceBlob = nullptr;
			HRESULT hr = m_Utils->CreateBlob(_shaderDescriptor->Source.data(), (UINT32)_shaderDescriptor->Source.size(), DXC_CP_UTF8, &sourceBlob);
			if (FAILED(hr))
			{
				// Return error result
				result.CompilationResult = Result::RESULT_ERROR;
				result.ErrorStr = "Failed to load shader file.";
				return result;
			}


			// Include handler
			IDxcIncludeHandler* includeHandler;
			m_Utils->CreateDefaultIncludeHandler(&includeHandler);


			// Target profile
			std::wstring targetProfile = ResolveDXCShaderType(_shaderDescriptor->Type);


			// Arguments
			std::wstring entryArg = L"-E";
			entryArg += entryPoint;

			std::vector<LPCWSTR> arguments = {
				//filePath.c_str(),
				L"-E", entryPoint.c_str(),
				L"-T", targetProfile.c_str(),
				//L"-fdxc-enable-dxil-reflection"
				//L"-I", directory.c_str(),
				//L"-D", L"D3D12",
			};


			std::vector<std::wstring> defineStrings;
			RHI_GraphicsAPI api = RHI_GraphicsAPI::RHI_GRAPHICS_API_INVALID;
			for (const auto& [key, value] : _shaderDescriptor->Defines)
			{
				if (key.empty() == false)
					defineStrings.push_back(StringToWString(key));
				if (value.empty() == false)
				{
					defineStrings.push_back(StringToWString(value));
					if (value == "D3D12")
						api = RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12;
					else if (value == "VULKAN")
						api = RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN;
				}
			}


			// Append defines AFTER base args
			for (const auto& def : defineStrings)
			{
				arguments.push_back(def.c_str());
			}


			// Buffer
			DxcBuffer buffer{};
			buffer.Encoding = DXC_CP_ACP;
			buffer.Ptr  = sourceBlob->GetBufferPointer();
			buffer.Size = sourceBlob->GetBufferSize();

			// Compile
			IDxcResult* res;
			hr = m_Compiler->Compile(&buffer, arguments.data(), (uint32)arguments.size(), includeHandler, IID_PPV_ARGS(&res));

			includeHandler->Release(); // TODO:: Look into making this into compiler level...

			if (FAILED(hr) || !res)
			{
				result.CompilationResult = Result::RESULT_ERROR;
				result.ErrorStr = "DXC Compile() call failed.";
				return result;
			}


			// Check status
			HRESULT status;
			res->GetStatus(&status);


			// Get error messages (even on success, there may be warnings)
			IDxcBlobEncoding* errorBlob;
			if (SUCCEEDED(res->GetErrorBuffer(&errorBlob)) && errorBlob)
			{
				std::string errors((const char*)errorBlob->GetBufferPointer(), errorBlob->GetBufferSize());
				result.ErrorStr = errors;

				if (FAILED(status))
				{
					result.CompilationResult = Result::RESULT_ERROR;
					errorBlob->Release();
					return result;
				}
			}

			// Get compiled shader
			IDxcBlob* shaderBlob;
			hr = res->GetResult(&shaderBlob);

			if (FAILED(hr) || !shaderBlob)
			{
				result.CompilationResult = Result::RESULT_ERROR;
				result.ErrorStr += "\nFailed to retrieve compiled shader.";
				return result;
			}


			// D3D12 SHADER REFLECTION
			// ===================================================
#if defined(COMPILE_GRAPHICS_API_DX12)
			if (api == RHI_GraphicsAPI::RHI_GRAPHICS_API_DIRECTX12)
			{
				IDxcBlob* reflectionBlob = nullptr;
				res->GetOutput(DXC_OUT_REFLECTION, IID_PPV_ARGS(&reflectionBlob), nullptr);


				if (reflectionBlob != nullptr)
				{
					DxcBuffer reflectionBuffer = {};
					reflectionBuffer.Ptr  = reflectionBlob->GetBufferPointer();
					reflectionBuffer.Size = reflectionBlob->GetBufferSize();


					ID3D12ShaderReflection* reflector;
					m_Utils->CreateReflection(&reflectionBuffer, IID_PPV_ARGS(&reflector));

					D3D_PRIMITIVE;
					reflector->GetGSInputPrimitive();

					D3D12_SHADER_DESC desc;
					reflector->GetDesc(&desc);

					uint32 inputParamterCount = desc.InputParameters;
					result.Reflection.ShaderInput = RHI_VertexLayout(inputParamterCount);
					for (uint32 i = 0; i < inputParamterCount; i++)
					{
						D3D12_SIGNATURE_PARAMETER_DESC param;
						reflector->GetInputParameterDesc(i, &param);

						uint32_t count = std::popcount(param.Mask);

						result.Reflection.ShaderInput[i] = Graphics::RHI_VertexElement(param.SemanticName, ResolveResourceFormat_From_RegisterComponentType(param.ComponentType, count));

						// Some error checking here, sumthing wong?
						if (i != param.SemanticIndex)
							Logger::Log("emmmmmm, please fix me... semantic index is fucking wrong!", LogLevel::LOG_LEVEL_WARNING);
					}


					uint32 outputParamterCount = desc.OutputParameters;
					result.Reflection.ShaderOutput = RHI_VertexLayout(outputParamterCount);
					for (uint32 i = 0; i < outputParamterCount; i++)
					{
						D3D12_SIGNATURE_PARAMETER_DESC param;
						reflector->GetOutputParameterDesc(i, &param);

						uint32_t count = std::popcount(param.Mask);

						result.Reflection.ShaderOutput[i] = Graphics::RHI_VertexElement(param.SemanticName, ResolveResourceFormat_From_RegisterComponentType(param.ComponentType, count));

						// Some error checking here, sumthing wong?
						if (i != param.SemanticIndex)
							Logger::Log("emmmmmm, please fix me... semantic index is fucking wrong!", LogLevel::LOG_LEVEL_WARNING);
					}

					reflectionBlob->Release();
				}
				else
				{
					Logger::Log("Unable to get reflectionData from the OutputResult.", LogLevel::LOG_LEVEL_WARNING);
				}
			}
#endif


			// VULKAN SHADER REFLECTION
			// ===================================================
#if defined(COMPILE_GRAPHICS_API_VK)
			if (api == RHI_GraphicsAPI::RHI_GRAPHICS_API_VULKAN)
			{
				SpvReflectShaderModule module;
				SpvReflectResult res = spvReflectCreateShaderModule(
					           shaderBlob->GetBufferSize(),
					(uint32_t*)shaderBlob->GetBufferPointer(),
					&module
				);


				if (res == SPV_REFLECT_RESULT_SUCCESS) 
				{
					uint32_t inputVariableCount = 0;
					spvReflectEnumerateInputVariables(&module, &inputVariableCount, nullptr);

					std::vector<SpvReflectInterfaceVariable*> inputVariables(inputVariableCount);
					spvReflectEnumerateInputVariables(&module, &inputVariableCount, inputVariables.data());

					result.Reflection.ShaderInput = RHI_VertexLayout(inputVariableCount);
					for (uint32_t i = 0; i < inputVariableCount; i++)
					{
						SpvReflectInterfaceVariable* var = inputVariables[i];

						// Skip builtins like gl_VertexIndex, gl_InstanceIndex, etc.
						if (var->decoration_flags & SPV_REFLECT_DECORATION_BUILT_IN)
							continue;

						uint32_t componentCount = 1;

						if (var->numeric.vector.component_count != 0)
							componentCount = var->numeric.vector.component_count;

					//	RHI_Format format = ResolveResourceFormat_From_SPIRV(
					//		var->numeric.scalar.width,
					//		var->numeric.scalar.signedness,
					//		componentCount
					//	);

					//	result.Reflection.ShaderInput[i] = Graphics::RHI_VertexElement(var->semantic, format);

						// Optional sanity check
						if (i != var->location)
						{
							Logger::Log(
								"Input variable location mismatch",
								LogLevel::LOG_LEVEL_WARNING
							);
						}
					}
				}

				// Don't forget to clean up
				spvReflectDestroyShaderModule(&module);
			}
#endif

			// Copy bytecode
			const uint8* data = reinterpret_cast<const uint8*>(shaderBlob->GetBufferPointer());
			size_t size = shaderBlob->GetBufferSize();

			result.ByteCode.assign(data, data + size);

			shaderBlob->Release();
			res->Release();

			return result;
		}
	}
}