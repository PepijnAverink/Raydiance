#pragma once
// Core includes
#include "./core/UUID.h"
#include "./core/error/result.h"
#include "./core/files/file_path.h"
#include "./core/files/file_system.h"


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
			static Result Load(const FilePath& _filepath, std::shared_ptr<ShaderAsset>& _asset);

			[[nodiscard]]
			Result Save();

		private:
			UUID m_UUID;
		};
	}
}