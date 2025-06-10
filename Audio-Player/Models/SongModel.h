#pragma once

#include "SongModel.g.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Core.h>

using namespace winrt::Windows::Foundation;

namespace winrt::Audio_Player::implementation
{
    struct SongModel : SongModelT<SongModel>
    {
        SongModel() = default;

        hstring Title();
        void Title(hstring const& value);

        hstring ImagePath();
        void ImagePath(hstring const& value);

        Uri SongPath();
        void SongPath(Uri const& value);    

        winrt::Windows::Media::Core::MediaSource MediaSource();
        void MediaSource(winrt::Windows::Media::Core::MediaSource const& value);

        int Id();
        void Id(int const& value);

    private:

        hstring m_title{};
        hstring m_imagePath{};
        Uri m_songPath{ nullptr };
        winrt::Windows::Media::Core::MediaSource m_source{ nullptr };
        int m_id{ 0 };

    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct SongModel : SongModelT<SongModel, implementation::SongModel>
    {
    };
}
