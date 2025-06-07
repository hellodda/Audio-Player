#include "pch.h"
#include "Locator.h"
#include "MainViewModel.h"

namespace winrt::Audio_Player::ViewModels
{
	MainViewModel Locator::MainViewModel()
	{
		static winrt::Audio_Player::MainViewModel s_mainViewModel;
		return s_mainViewModel;
	}
}