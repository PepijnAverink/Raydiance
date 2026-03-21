#pragma once

namespace Raydiance
{
	namespace Graphics
	{
		struct RHI_AdapterFeatures
		{
		public:
			// Default constructor and descructor
			// =========================================
					 RHI_AdapterFeatures(void) = default;
			virtual ~RHI_AdapterFeatures(void) = default;

			[[nodiscard]] inline constexpr bool IsAnistropicFilteringSupported() const { return m_AnistropicFilteringSupport; }

		protected:
			bool m_AnistropicFilteringSupport = false;
		};
	}
}