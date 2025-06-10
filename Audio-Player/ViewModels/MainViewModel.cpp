#include "pch.h"
#include "MainViewModel.h"

#if __has_include("MainViewModel.g.cpp")
#  include "MainViewModel.g.cpp"
#endif

#include <Framework/RelayCommand.h>
#include <Helpers/FilePicker.h>

namespace winrt::Audio_Player::implementation
{
    MainViewModel::MainViewModel() = default;

    void MainViewModel::Inject(std::shared_ptr<ILogger> logger,
        std::shared_ptr<ISongProvider> provider)
    {
        m_logger = std::move(logger);
        m_songProvider = std::move(provider);
        m_logger->LogInfo("MainViewModel::Inject called");
        InitializeSongsAsync();
        m_logger->LogInfo("MainViewModel::Inject completed");
    }

    IObservableVector<winrt::Audio_Player::SongModel> MainViewModel::Songs()
    {
        m_logger->LogInfo("MainViewModel::Songs getter called");
        return m_songs;
    }

    void MainViewModel::Songs(IObservableVector<winrt::Audio_Player::SongModel> const& value)
    {
        m_logger->LogInfo("MainViewModel::Songs setter called");
        m_songs = value;
    }

    Audio_Player::SongModel MainViewModel::SelectedSong()
    {
        m_logger->LogInfo("MainViewModel::SelectedSong getter called");
        return m_selectedSong;
    }

    void MainViewModel::SelectedSong(Audio_Player::SongModel const& value)
    {
        if (m_selectedSong != value)
        {
            m_selectedSong = value;
            m_logger->LogInfo("MainViewModel::SelectedSong changed to ID: " + std::to_string(m_selectedSong.Id()));
            RaisePropertyChanged(L"SelectedSong");
        }
        else
        {
            m_logger->LogInfo("MainViewModel::SelectedSong set to same value, no change");
        }
    }

    IAsyncAction MainViewModel::InitializeSongsAsync()
    {
        m_logger->LogInfo("MainViewModel::InitializeSongsAsync started");
        auto songs = co_await m_songProvider->GetAllSongsAsync();
        m_logger->LogInfo("MainViewModel::InitializeSongsAsync retrieved " + std::to_string(songs.Size()) + " songs");
        for (auto& s : songs)
        {
            m_songs.Append(s);
            m_logger->LogInfo("MainViewModel::InitializeSongsAsync appended Song ID: " + std::to_string(s.Id()));
        }
        m_logger->LogInfo("MainViewModel::InitializeSongsAsync completed");
        co_return;
    }

    ICommand MainViewModel::AddCommand()
    {
        if (!m_addCommand)
        {
            m_addCommand = winrt::make<RelayCommand>(
                [this]() -> IAsyncAction
                {
                    m_logger->LogInfo("MainViewModel::AddCommand invoked");
                    co_await Helpers::FilePicker::PickAndCopyFileAsync(
                        nullptr,
                        m_songProvider->GetDefaultPath()
                    );
                    m_logger->LogInfo("MainViewModel::AddCommand file picked and copied");
                    co_await InitializeSongsAsync();
                    m_logger->LogInfo("MainViewModel::AddCommand completed");
                }
            );
        }
        return m_addCommand;
    }

    ICommand MainViewModel::DeleteCommand()
    {
        if (!m_deleteCommand)
        {
            m_deleteCommand = winrt::make<RelayCommand>(
                [this]() -> IAsyncAction
                {
                    m_logger->LogInfo("MainViewModel::DeleteCommand invoked");
                    if (m_selectedSong)
                    {
                        m_logger->LogInfo("MainViewModel::DeleteCommand deleting Song ID: " + std::to_string(m_selectedSong.Id()));
                        co_await m_songProvider->DeleteByIdAsync(m_selectedSong.Id());
                        m_logger->LogInfo("MainViewModel::DeleteCommand deletion completed for ID: " + std::to_string(m_selectedSong.Id()));
                    }
                    else
                    {
                        m_logger->LogWarning("MainViewModel::DeleteCommand called with no SelectedSong");
                    }
                    co_return;
                }
            );
        }
        return m_deleteCommand;
    }
}
