#include "pch.h"
#include "SongModel.h"

#if __has_include("SongModel.g.cpp")
#  include "SongModel.g.cpp"
#endif

namespace winrt::Audio_Player::implementation
{
    hstring SongModel::Title() const noexcept
    {
        return m_title;
    }
    void SongModel::Title(hstring const& value) noexcept
    {
        m_title = value;
    }

    hstring SongModel::Author() const noexcept
    {
        return m_author;
    }

    void SongModel::Author(hstring const& value) noexcept
    {
        if (m_author != value)
        {
            m_author = value;
        }
    }

    BitmapImage SongModel::Image()
    {
        return m_image;
    }

    void SongModel::Image(BitmapImage const& value)
    {
        if (m_image != value)
        {
            m_image = value;
        }
    }

    hstring SongModel::SongPath() const noexcept
    {
        return m_songPath;
    }
    void SongModel::SongPath(hstring const& value) noexcept
    {
        if (m_songPath != value)
        {
            m_songPath = value;
        }
    }

    winrt::Windows::Media::Core::MediaSource SongModel::MediaSource() const noexcept
    {
        return m_source;
    }
    void SongModel::MediaSource(winrt::Windows::Media::Core::MediaSource const& value) noexcept
    {
        if (m_source != value)
        {
            m_source = value;
        }
    }

    int SongModel::Id() const noexcept
    {
        return m_id;
    }
    void SongModel::Id(int const& value) noexcept
    {
        if (m_id != value)
        {
            m_id = value;
        }
    }
}
