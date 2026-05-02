#pragma once
// Core includes
#include "./core/UUID.h"
#include "./core/error/result.h"
#include "./core/files/file_path.h"
#include "./core/files/file_system.h"


namespace Raydiance
{
	namespace Graphics
	{
		class MaterialAsset
		{
		public:
			[[nodiscard]]
			static Result CreateEmpty(void);

			[[nodiscard]]
			static Result Load(const FilePath& _filepath);

			[[nodiscard]]
			Result Save(const FilePath& _filepath);
		};
	}
}