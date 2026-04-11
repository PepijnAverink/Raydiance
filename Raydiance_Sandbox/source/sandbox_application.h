#pragma once
#include "./core/application.h"

namespace Sandbox
{
	using namespace Raydiance;
	class SandboxApplication final : public Raydiance::Application
	{
	public:
				 SandboxApplication(void);
		virtual ~SandboxApplication(void);

		virtual Result Initialize(const PlatformType& _platformType, const FilePath& _filepath) override;

	private:

	};
}
