#include "stdafx.h"
#include "sandbox_application.h"

// #define USE_DEBUG_ALLOCATOR
// #include "./core/memory/allocator/debug_allocator.h"

#include "./graphics/gfx/render_backend.h"


// TEST INCLUDES
// TODO:: REMOVE THESE HERE
// -------------------------------------------------------
#include "./graphics/gfx/material/material_asset.h"
#include "./graphics/RHI/resource/shader/shader_asset.h"
// -------------------------------------------------------


namespace Sandbox
{
	SandboxApplication::SandboxApplication()
		: Raydiance::Application()
	{
		//Raydiance::Graphics::RenderBackend::Create();

		printf("\nSANDBOX TURTLE!\n");
	}

	SandboxApplication::~SandboxApplication(void)
	{

	}

	Result SandboxApplication::Initialize(const PlatformType& _platformType, const FilePath& _filepath)
	{
		// Initialize base application
		Result result = Application::Initialize(_platformType, _filepath);
		if (CheckError(result) == true)
		{
			Logger::Log("Something went wrong while initializing the application.", LogLevel::LOG_LEVEL_ERROR);
			Logger::Log("No further evidence what went wrong, please see earlier logs.", LogLevel::LOG_LEVEL_ERROR);
			return result;
		}


		// std::shared_ptr<Raydiance::Graphics::MaterialAsset> materialAsset;
		// Raydiance::Result res = Raydiance::Graphics::MaterialAsset::CreateEmpty(materialAsset);
		// 
		// materialAsset->Save();

		//std::shared_ptr<Raydiance::Graphics::ShaderAsset> shaderAsset;
		//Raydiance::Result res = Raydiance::Graphics::ShaderAsset::CreateEmpty(shaderAsset);
		//
		//shaderAsset->m_EntryPoint = "main";
		//shaderAsset->m_ShaderFilePath = FilePath("./assets/pixel_shader.hlsl");
		//
		//shaderAsset->m_ShaderType = Raydiance::Graphics::RHI_ShaderType::RHI_SHADER_TYPE_PIXEL;
		//
		//shaderAsset->Save();

		// Raydiance::Graphics::RHI_Shader* shader = nullptr;
		// Raydiance::Result res = Raydiance::Graphics::ShaderAsset::Load_RHI_Shader(Raydiance::FilePath("./assets/bin/a9d2a84105fd963ca9c1558a1b7fc776.rash"), &shader);
		// if (CheckError(res) == true)
		// {
		// 	Logger::Log("Failed to load shader asset.", LogLevel::LOG_LEVEL_ERROR);
		// 	//return res;
		// }
		// 
		// if (shader != nullptr)
		// 	delete shader;


		return Result::RESULT_GOOD;
	}
}

Raydiance::Application* CreateApplication()
{
	return new Sandbox::SandboxApplication();
}