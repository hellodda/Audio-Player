#include "pch.h"
#include "SongModel.h"
#if __has_include("SongModel.g.cpp")
#include "SongModel.g.cpp"
#endif

namespace winrt::Audio_Player::implementation
{
    hstring SongModel::Title()
    {
        return m_title;
    }
    void SongModel::Title(hstring const& value)
    {
        m_title = value;
    }
    hstring SongModel::ImagePath()
    {
        return m_imagePath;
    }
    void SongModel::ImagePath(hstring const& value)
    {
        m_imagePath = value;
    }
    Uri SongModel::SongPath()
    {
        return m_songPath;
    }
    void SongModel::SongPath(Uri const& value)
    {
        if (m_songPath != value)
        {
            m_songPath = value;
        }
    }
    winrt::Windows::Media::Core::MediaSource SongModel::MediaSource()
    {
        return m_source;
    }
    void SongModel::MediaSource(winrt::Windows::Media::Core::MediaSource const& value)
    {
        if (m_source != value)
        {
            m_source = value;
        }
    }
    int SongModel::Id()
    {
        return m_id;
    }
    void SongModel::Id(int const& value)
    {
        if (m_id != value)
        {
            m_id = value;
        }
    }
}
