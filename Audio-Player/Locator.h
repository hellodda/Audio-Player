#pragma once
#include "MainViewModel.h"

namespace winrt::Audio_Player::ViewModels
{
	struct Locator abstract sealed
	{
		static winrt::Audio_Player::MainViewModel MainViewModel();
	};
}

