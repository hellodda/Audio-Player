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

        hstring Title() const noexcept;
        void Title(hstring const& value) noexcept;

        hstring ImagePath() const noexcept;
        void ImagePath(hstring const& value) noexcept;

        hstring SongPath() const noexcept;
        void SongPath(hstring const& value) noexcept;

        winrt::Windows::Media::Core::MediaSource MediaSource() const noexcept;
        void MediaSource(winrt::Windows::Media::Core::MediaSource const& value) noexcept;

        int Id() const noexcept;
        void Id(int const& value) noexcept;

    private:
        hstring m_title{};
        hstring m_imagePath{};
        hstring m_songPath{};
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
