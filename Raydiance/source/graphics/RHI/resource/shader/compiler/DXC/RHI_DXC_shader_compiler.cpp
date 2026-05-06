#include "./pch.h"
#include "./graphics/RHI/resource/shader/compiler/DXC/RHI_DXC_shader_compiler.h"

#include "./util/string_util.h"


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
			delete m_Utils;
			delete m_Compiler;
			delete m_Library;
		}


		RHI_ShaderCompileResult RHI_DXC_ShaderCompiler::Compile(const RHI_ShaderCompileDescriptor* _shaderDescriptor)
		{
			// Function result
			RHI_ShaderCompileResult result {};
			result.CompilationResult = Result::RESULT_GOOD;


			// Convert strings once (avoid dangling pointers)
			std::wstring filePath   = StringToWString(_shaderDescriptor->FilePath.GetPath());
			std::wstring directory  = StringToWString(_shaderDescriptor->FilePath.GetDirectory());
			std::wstring entryPoint = StringToWString(_shaderDescriptor->EntryPoint);


			// Load file
			uint32_t codePage = DXC_CP_ACP;
			IDxcBlobEncoding* sourceBlob;


			// Load the actual file from disk
			HRESULT hr = m_Utils->LoadFile(filePath.c_str(), &codePage, &sourceBlob);
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
			std::wstring targetProfile = L"vs_6_3";


			// Arguments
			std::wstring entryArg = L"-E";
			entryArg += entryPoint;

			std::vector<LPCWSTR> arguments = {
				filePath.c_str(),
				entryArg.c_str(),
				L"-T", targetProfile.c_str(),
				L"-I", directory.c_str(),
				L"-D", L"D3D12",
			};

			std::vector<std::wstring> defineStrings;
			std::vector<LPCWSTR> defineArgs;

			// desc.Defines = {
			// { "USE_SHADOWS", "1" },
			// { "MAX_LIGHTS", "8" },
			// { "DEBUG", "" } // just #define DEBUG
			// };
			for (const auto& [key, value] : _shaderDescriptor->Defines)
			{
				std::wstring def = L"-D" + StringToWString(key);

				if (!value.empty())
				{
					def += L"=" + StringToWString(value);
				}

				defineStrings.push_back(def);
			}


			// Append defines AFTER base args
			for (const auto& def : defineStrings)
			{
				arguments.push_back(def.c_str());
			}


			// Buffer
			DxcBuffer buffer{};
			buffer.Encoding = DXC_CP_ACP;
			buffer.Ptr      = sourceBlob->GetBufferPointer();
			buffer.Size     = sourceBlob->GetBufferSize();

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

			// Copy bytecode
			uint8_t* data = reinterpret_cast<uint8_t*>(shaderBlob->GetBufferPointer());
			size_t size = shaderBlob->GetBufferSize();

			result.ByteCode.assign(data, data + size);

			shaderBlob->Release();
			res->Release();

			return result;
		}
	}
}