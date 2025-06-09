#pragma once

#include "SongModel.g.h"
#include <winrt/Windows.Foundation.h>

namespace winrt::Audio_Player::implementation
{
    struct SongModel : SongModelT<SongModel>
    {
        SongModel() = default;

        winrt::hstring Title();
        void Title(winrt::hstring const& value);

        winrt::hstring ImagePath();
        void ImagePath(winrt::hstring const& value);

        int Id();
        void Id(int const& value);

    private:

        winrt::hstring m_title{};
        winrt::hstring m_imagePath{};
        int m_id{ 0 };

    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct SongModel : SongModelT<SongModel, implementation::SongModel>
    {
    };
}
