#include "./pch.h"

#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader.h"
#include "./graphics/RHI_api/vk/resource/shader/RHI_VK_shader_type.h"

#include "./graphics/RHI_api/vk/RHI_VK_render_device.h"

#include "./util/string_util.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <assert.h>

#include <./atlbase.h>
#include <./dxc/dxcapi.h>
#include <./d3d12shader.h>


// SPIRV-reflect
#include "./spirv_reflect.h"


#include <iostream>

namespace Raydiance
{
	namespace Graphics
	{
		static CComPtr<IDxcCompiler3> s_Compiler = nullptr;
		static CComPtr<IDxcLibrary> s_Library = nullptr;
		static CComPtr<IDxcUtils> s_Utils = nullptr;

		RHI_VK_Shader::RHI_VK_Shader()
			: RHI_Shader()
		{ }

		RHI_VK_Shader::~RHI_VK_Shader()
		{
			vkDestroyShaderModule(((RHI_VK_RenderDevice*)RHI_RenderDevice::Get())->GetVKDevice(), m_ShaderModule, nullptr);
		}

		const Result RHI_VK_Shader::Initialize(RHI_VK_RenderDevice* _RHI_RenderDevice, const RHI_ShaderDescriptor* _shaderDescriptor)
		{
			Result result = RHI_Shader::Initialize(_shaderDescriptor);
			if (CheckError(result) == true)
			{
				// Log error
				return result;
			}

			// Get the filepaths
			std::string filepath = _shaderDescriptor->FilePath.GetPath();
			//std::string compileFilepath = ReplaceFileExtension(filepath, ".spv");

			// Check if the shaders exist
			//bool exist = FileSystem::FileExists(filepath);
			//bool compiledExist = FileSystem::FileExists(compileFilepath);

			// Error if file does not exist
			//if (exist == false && compiledExist == false)
			//{
			//	Logger::Log("User tried to load shader file that does not exist.", LogLevel::LOG_LEVEL_ERROR);
			//	return;
			//}
			bool compiledExist = false;
			//if (compiledExist == true && (FileSystem::GetModificationHash(filepath) < FileSystem::GetModificationHash(compileFilepath) || exist == false))
			//{
			//	// Read shader code
			//	void* code = nullptr;
			//	size_t size = 0;
			//	FileSystem::ReadFile(_shaderDescriptor->FilePath, &code, size);
			//
			//	VkShaderModuleCreateInfo createInfo{};
			//	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
			//	createInfo.codeSize = size;
			//	createInfo.pCode = reinterpret_cast<const uint32_t*>(code);
			//
			//	// Crate shader module ander error check
			//	if (vkCreateShaderModule(_RHI_RenderDevice->GetDevice(), &createInfo, nullptr, &m_ShaderModule) != VK_SUCCESS)
			//	{
			//		Logger::Log("VK_ERROR - Failed to create shader module.", LogLevel::LOG_LEVEL_ERROR);
			//		return;
			//	}
			//}
			//else
			{
				HRESULT hres;
				if (!s_Compiler)
				{
					// Initialize DXC library
					hres = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&s_Library));
					if (FAILED(hres)) {
						throw std::runtime_error("Could not init DXC Library");
					}

					// Initialize DXC compiler
					hres = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&s_Compiler));
					if (FAILED(hres)) {
						throw std::runtime_error("Could not init DXC Compiler");
					}

					// Initialize DXC utility
					hres = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&s_Utils));
					if (FAILED(hres)) {
						throw std::runtime_error("Could not init DXC Utiliy");
					}
				}


				// Load the HLSL text shader from disk
				uint32_t codePage = DXC_CP_ACP;
				IDxcBlobEncoding* sourceBlob;
				hres = s_Utils->LoadFile(StringToWString(_shaderDescriptor->FilePath.GetPath()).c_str(), &codePage, &sourceBlob);
				if (FAILED(hres)) {
					Logger::Log("Could not load shader file", LogLevel::LOG_LEVEL_ERROR);
				}

				IDxcIncludeHandler* includeHandler;
				s_Utils->CreateDefaultIncludeHandler(&includeHandler);

				std::wstring tp = ResolveVKShaderType(_shaderDescriptor->Type).c_str();
				LPCWSTR targetProfile = tp.c_str();

				std::wstring dir = StringToWString(_shaderDescriptor->FilePath.GetDirectory());
				LPCWSTR directory = dir.c_str();

				// Configure the compiler arguments for compiling the HLSL shader to SPIR-V
				std::vector<LPCWSTR> arguments = {
					// (Optional) name of the shader file to be displayed e.g. in an error message
					StringToWString(_shaderDescriptor->FilePath.GetPath()).c_str(),
					// Shader main entry point
					L"-E", StringToWString(_shaderDescriptor->EntryPoint).c_str(),
					// Shader target profile
					L"-T", targetProfile,
					L"-D", L"VULKAN",
					L"-I", directory,
					// Compile to SPIRV
					L"-spirv",
					L"-fvk-use-dx-layout",
					L"-fspv-reflect"
				};

				//if (_shaderDescriptor->Type == RHI_ShaderType::SHADER_TYPE_RAY_GEN || _shaderDescriptor->Type == ShaderType::SHADER_TYPE_MISS || _shaderDescriptor->Type == ShaderType::SHADER_TYPE_CLOSEST_HIT)
				//{
				//	arguments.push_back(L"-fspv-target-env=vulkan1.2");
				//}

				// Compile shader
				DxcBuffer buffer{};
				buffer.Encoding = DXC_CP_ACP;
				buffer.Ptr = sourceBlob->GetBufferPointer();
				buffer.Size = sourceBlob->GetBufferSize();

				CComPtr<IDxcResult> result{ nullptr };
				hres = s_Compiler->Compile(&buffer, arguments.data(), (uint32_t)arguments.size(), includeHandler, IID_PPV_ARGS(&result));

				//ID3D12ShaderReflection;

				if (SUCCEEDED(hres)) {
					result->GetStatus(&hres);
				}

				// Output error if compilation failed
				if (FAILED(hres) && (result)) {
					CComPtr<IDxcBlobEncoding> errorBlob;
					hres = result->GetErrorBuffer(&errorBlob);
					if (SUCCEEDED(hres) && errorBlob) {
						std::cerr << "Shader compilation failed :\n\n" << (const char*)errorBlob->GetBufferPointer();
						throw std::runtime_error("Compilation failed");
					}
				}

				// Get compilation result
				CComPtr<IDxcBlob> code;
				result->GetResult(&code);


				// Create a Vulkan shader module from the compilation result
				VkShaderModuleCreateInfo shaderModuleCI{};
				shaderModuleCI.sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
				shaderModuleCI.codeSize = code->GetBufferSize();
				shaderModuleCI.pCode    = (uint32_t*)code->GetBufferPointer();
				vkCreateShaderModule(_RHI_RenderDevice->GetVKDevice(), &shaderModuleCI, nullptr, &m_ShaderModule);

				includeHandler->Release();


				SpvReflectShaderModule module;
				SpvReflectResult res = spvReflectCreateShaderModule(
					code->GetBufferSize(),
					(uint32_t*)code->GetBufferPointer(),
					&module
				);

				if (res != SPV_REFLECT_RESULT_SUCCESS) {
					// Handle error
					return Result::RESULT_ERROR;
				}

				// 1. Get Descriptor Bindings
				uint32_t count = 0;
				spvReflectEnumerateDescriptorBindings(&module, &count, nullptr);
				std::vector<SpvReflectDescriptorBinding*> bindings(count);
				spvReflectEnumerateDescriptorBindings(&module, &count, bindings.data());

				for (auto* b : bindings) {
					std::cout << "Binding: " << b->name
						<< " | Set: " << b->set
						<< " | Binding: " << b->binding
						<< " | Type: " << b->descriptor_type << "\n";
				}

				// 2. Get Push Constants
				uint32_t pcCount = 0;
				spvReflectEnumeratePushConstantBlocks(&module, &pcCount, nullptr);
				std::vector<SpvReflectBlockVariable*> pushConstants(pcCount);
				spvReflectEnumeratePushConstantBlocks(&module, &pcCount, pushConstants.data());

				for (auto* pc : pushConstants) {
					std::cout << "Push Constant: " << pc->name
						<< " | Size: " << pc->size << " bytes\n";
				}

				// Don't forget to clean up
				spvReflectDestroyShaderModule(&module);
			}

			return Result::RESULT_GOOD;
		}
	}
}