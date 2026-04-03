#include "./pch.h"
#include "./core/application.h"

namespace Raydiance
{
	Application::Application(void)
	{

	}

	Application::~Application(void)
	{

	}

	Result Application::Initialze(const PlatformType& _platformType)
	{
		return Result::RESULT_GOOD;
	}

	Result Application::Initialze(const PlatformType& _platformType, const FilePath& _filepath)
	{
		return Result::RESULT_GOOD;
	}

	Result Application::Terminate(void)
	{
		return Result::RESULT_GOOD;
	}

	Result Application::Run(void)
	{
		return Result::RESULT_GOOD;
	}
}