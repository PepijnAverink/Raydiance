#include "./pch.h"
#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader.h"
#include "./graphics/RHI_api/dx12/resource/shader/RHI_DX12_shader_type.h"


#include <D3Dcompiler.h>

#include "./utility/string_utility.h"
#include "./core/system/file_system.h"

namespace Raydiance
{
	namespace Graphics
	{
		static Microsoft::WRL::ComPtr<IDxcCompiler3> s_Compiler = nullptr;
		static Microsoft::WRL::ComPtr<IDxcLibrary>   s_Library = nullptr;
		static Microsoft::WRL::ComPtr<IDxcUtils>     s_Utils = nullptr;

		RHI_DX12_Shader::RHI_DX12_Shader(RHI_DX12_RenderDevice* _renderDevice, const RHI_ShaderDescriptor* _shaderDescriptor)
			: RHI_Shader(_shaderDescriptor)
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

			HRESULT hr;
			ID3DBlob* errorBuff;

			// Get the filepaths
			std::string filepath = _shaderDescriptor->Filepath;
			std::string compileFilepath = ReplaceFileExtension(filepath, ".cso");

			// Check if the shaders exist
			bool exist = FileSystem::FileExists(filepath);
			bool compiledExist = FileSystem::FileExists(compileFilepath);

			// Error if file does not exist
			if (exist == false && compiledExist == false)
			{
				Logger::Log("User tried to load shader file that does not exist.", LogType::LOG_TYPE_ERROR);
				return;
			}

			//if (compiledExist && (FileSystem::GetModificationHash(filepath) < FileSystem::GetModificationHash(compileFilepath) || exist == false) && m_CompiledOptions.ForceRecompile == false)
			//{
			//	// Read shader code
			//	void* code = nullptr;
			//	size_t size = 0;
			//	FileSystem::ReadFile(compileFilepath, &code, size);
			//
			//	m_ShaderByteCode.pShaderBytecode = code;
			//	m_ShaderByteCode.BytecodeLength = size;
			//}
			//else
			{
				// Load the HLSL text shader from disk
				uint32_t codePage = DXC_CP_ACP;
				IDxcBlobEncoding* sourceBlob;
				hr = s_Utils->LoadFile(StringToWString(_shaderDescriptor->Filepath).c_str(), &codePage, &sourceBlob);
				if (FAILED(hr)) {
					Logger::Log("Could not load shader file", LogType::LOG_TYPE_ERROR);
					return;
				}

				IDxcIncludeHandler* includeHandler;
				s_Utils->CreateDefaultIncludeHandler(&includeHandler);

				std::wstring tp = ResolveDX12ShaderType(m_Type).c_str();
				LPCWSTR targetProfile = tp.c_str();

				//	std::wstring dir = StringToWString(_shaderDescriptor->FilePath.GetDirectory());
				//	LPCWSTR directory = dir.c_str();


					// Configure the compiler arguments for compiling the HLSL shader to SPIR-V
				std::wstring entryPoint_argument = L"-E" + StringToWString(m_EntryPoint);
				std::vector<LPCWSTR> arguments = {
					// (Optional) name of the shader file to be displayed e.g. in an error message
					StringToWString(_shaderDescriptor->Filepath).c_str(),
					// Shader main entry point
					entryPoint_argument.c_str(),
					// Shader target profile
					L"-T", targetProfile,
					L"-D", L"D3D12",
					//	L"-I", directory,
				};

				//if (m_CompiledOptions.Debug == DebugOutput::DEBUG_OUTPUT_MINIMAL)
				//{
				//	arguments.push_back(L"-Zs");
				//}
				//else if (m_CompiledOptions.Debug == DebugOutput::DEBUG_OUTPUT_FULL)
				//{
				//	arguments.push_back(L"-Zi");
				//}

				// Compile shader
				DxcBuffer buffer{};
				buffer.Encoding = DXC_CP_ACP;
				buffer.Ptr = sourceBlob->GetBufferPointer();
				buffer.Size = sourceBlob->GetBufferSize();

				Microsoft::WRL::ComPtr<IDxcResult> result{ nullptr };
				hr = s_Compiler->Compile(&buffer, arguments.data(), (uint32_t)arguments.size(), includeHandler, IID_PPV_ARGS(&result));

				if (SUCCEEDED(hr)) {
					result->GetStatus(&hr);
				}

				// Output error if compilation failed
				if (FAILED(hr) && (result)) {
					Microsoft::WRL::ComPtr<IDxcBlobEncoding> errorBlob;
					hr = result->GetErrorBuffer(&errorBlob);
					if (SUCCEEDED(hr) && errorBlob) {
						wprintf(L"Compilation failed with errors:\n%hs\n", (const char*)errorBlob->GetBufferPointer());
					}
				}

				// Delete old shader if it was loaded
				if (m_ShaderBytes != nullptr)
					m_ShaderBytes->Release();

				// Assign new shader
				result->GetResult(&m_ShaderBytes);

				m_ShaderByteCode.pShaderBytecode = m_ShaderBytes->GetBufferPointer();
				m_ShaderByteCode.BytecodeLength = m_ShaderBytes->GetBufferSize();

				FileSystem::WriteFile(compileFilepath, m_ShaderBytes->GetBufferPointer(), m_ShaderBytes->GetBufferSize());

				includeHandler->Release();

				// Output the debug file
				//if (m_CompiledOptions.Debug == DebugOutput::DEBUG_OUTPUT_MINIMAL || m_CompiledOptions.Debug == DebugOutput::DEBUG_OUTPUT_FULL)
				//{
				//	IDxcBlob* pDebugData;
				//	IDxcBlobUtf16* pDebugDataPath;
				//	result->GetOutput(DXC_OUT_PDB, IID_PPV_ARGS(&pDebugData), &pDebugDataPath);
				//
				//	//FileSystem::WriteFile(ReplaceFileExtension(compileFilepath, ".pdb"), pDebugData->GetBufferPointer(), pDebugData->GetBufferSize());
				//}
			}
		}
		
		
		RHI_DX12_Shader::~RHI_DX12_Shader()
		{ 
			if (m_ShaderBytes != nullptr)
				m_ShaderBytes->Release();
		}
	}
}