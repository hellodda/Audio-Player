#pragma once

#include "SongModel.g.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.Core.h>
#include <winrt/Microsoft.UI.Xaml.Media.Imaging.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml::Media::Imaging;

namespace winrt::Audio_Player::implementation
{
    struct SongModel : SongModelT<SongModel>
    {
        SongModel() = default;

        hstring Title() const noexcept;
        void Title(hstring const& value) noexcept;

        hstring Author() const noexcept;
        void Author(hstring const& value) noexcept;

        BitmapImage Image();
        void Image(BitmapImage const& value);

        hstring SongPath() const noexcept;
        void SongPath(hstring const& value) noexcept;

        winrt::Windows::Media::Core::MediaSource MediaSource() const noexcept;
        void MediaSource(winrt::Windows::Media::Core::MediaSource const& value) noexcept;

        int Id() const noexcept;
        void Id(int const& value) noexcept;

    private:
        hstring m_title{};
        hstring m_author{};
        BitmapImage m_image{};
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
