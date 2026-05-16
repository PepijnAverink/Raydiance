#pragma once
// Core includes
#include "./core/UUID.h"
#include "./core/error/result.h"
#include "./core/files/file_path.h"
#include "./core/files/file_system.h"


// Graphics includes
#include "./graphics/RHI/resource/shader/RHI_shader.h"
#include "./graphics/RHI/resource/shader/RHI_shader_type.h"


// Generic includes
#include <memory>


// Util includes
#include "./util/version.h"


// Defines
#define SHADER_ASSET_ACTIVE_VERSION Version(1, 0, 0, 0)


namespace Raydiance
{
	namespace Graphics
	{
		class ShaderAsset
		{
		public:
			[[nodiscard]]
			static Result CreateEmpty(std::shared_ptr<ShaderAsset>& _asset);

			[[nodiscard]]
			static Result CreateFromShader(std::shared_ptr<ShaderAsset>& _asset);

			[[nodiscard]]
			static Result Load(const FilePath& _filepath, std::shared_ptr<ShaderAsset>& _asset);

			[[nodiscard]]
			Result Save();


			[[nodiscard]]
			static Result Load_RHI_Shader(const FilePath& _filepath, RHI_Shader** _shader);

			FilePath m_ShaderFilePath;

			RHI_ShaderType m_ShaderType = RHI_ShaderType::RHI_SHADER_TYPE_INVALID;

			std::string m_EntryPoint;

		private:
			UUID     m_UUID;
		};
	}
}