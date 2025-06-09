#pragma once

#include <winrt/Microsoft.UI.Xaml.h>

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::Audio_Player::Helpers
{
	struct FilePicker
	{
		static IAsyncAction PickAndCopyFileAsync(XamlRoot const& root, hstring const& to);
	};
}

