#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "ILogger.h"
#include <Models/SongModel.h>

namespace winrt::Audio_Player::Framework
{
	struct ISongProvider
	{
		virtual winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVector<SongModel>> GetAllSongsAsync() = 0;
	};
}