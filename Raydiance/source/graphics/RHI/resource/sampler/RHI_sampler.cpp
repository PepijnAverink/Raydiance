#include "./pch.h"
#include "./graphics/RHI/resource/sampler/RHI_sampler.h"


namespace Raydiance
{
	namespace Graphics
	{
		RHI_Sampler::RHI_Sampler(void)
		{ }

		RHI_Sampler::~RHI_Sampler(void)
		{ }

		const Result RHI_Sampler::Intiialize(const RHI_SamplerDescriptor& _samplerDescriptor)
		{
			// Validate descriptor
			if (_samplerDescriptor.Filter == RHI_FilterMode::RHI_FILTER_MODE_INVALID)
			{
				Logger::Log(std::format("Error: the filter mode provided is invalid: {}", RHI_FilterModeToString(_samplerDescriptor.Filter)), LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Apply filter modes
			m_MinFilter = _samplerDescriptor.Filter;
			m_MagFilter = _samplerDescriptor.Filter;
			m_MipFilter = _samplerDescriptor.Filter;


			// Validate descriptor
			if (_samplerDescriptor.AddressU == RHI_AddressMode::RHI_ADDRESS_MODE_INVALID || 
				_samplerDescriptor.AddressV == RHI_AddressMode::RHI_ADDRESS_MODE_INVALID || 
				_samplerDescriptor.AddressW == RHI_AddressMode::RHI_ADDRESS_MODE_INVALID)
			{
				Logger::Log(std::format("Error: the address mode provided is invalid: {}, {}, {}", RHI_AddressModeToString(_samplerDescriptor.AddressU), RHI_AddressModeToString(_samplerDescriptor.AddressV), RHI_AddressModeToString(_samplerDescriptor.AddressW)), LogType::LOG_TYPE_ERROR);
				return Result::RESULT_ERROR;
			}

			// Apply addressing modes
			m_AddressU = _samplerDescriptor.AddressU;
			m_AddressV = _samplerDescriptor.AddressV;
			m_AddressW = _samplerDescriptor.AddressW;

			return Result::RESULT_GOOD;
		}
	}
}