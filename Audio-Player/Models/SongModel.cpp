#include "pch.h"
#include "SongModel.h"
#if __has_include("SongModel.g.cpp")
#include "SongModel.g.cpp"
#endif

namespace winrt::Audio_Player::implementation
{
    winrt::hstring SongModel::Title()
    {
        return m_title;
    }
    void SongModel::Title(winrt::hstring const& value)
    {
        m_title = value;
    }
    winrt::hstring SongModel::ImagePath()
    {
        return m_imagePath;
    }
    void SongModel::ImagePath(winrt::hstring const& value)
    {
        m_imagePath = value;
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
