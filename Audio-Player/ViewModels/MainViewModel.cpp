#include "pch.h"
#include "MainViewModel.h"
#if __has_include("MainViewModel.g.cpp")
#include "MainViewModel.g.cpp"
#endif

#include <Framework/RelayCommand.h>
#include <Helpers/FilePicker.h>

namespace winrt::Audio_Player::implementation
{
	MainViewModel::MainViewModel()
	{
		
	}
	void MainViewModel::Inject(std::shared_ptr<ILogger> logger, std::shared_ptr<ISongProvider> provider)
	{
		m_logger = std::move(logger);
		m_songProvider = std::move(provider);
		m_logger->LogInfo("Inject from MainViewModel called");
		InitializeSongsAsync();
	}
	IObservableVector<winrt::Audio_Player::SongModel> MainViewModel::Songs()
	{
		return m_songs;
	}
	void MainViewModel::Songs(IObservableVector<winrt::Audio_Player::SongModel> const& value)
	{
		m_songs = value;
	}
	Audio_Player::SongModel MainViewModel::SelectedSong()
	{
		return m_selectedSong;
	}
	void MainViewModel::SelectedSong(Audio_Player::SongModel const& value)
	{
		if (m_selectedSong != value)
		{
			m_selectedSong = value;
			RaisePropertyChanged(L"SelectedSong");
		}
	}
	IAsyncAction MainViewModel::InitializeSongsAsync()
	{
		auto songs = co_await m_songProvider->GetAllSongsAsync();
		for (auto& s : songs)
		{
			m_songs.Append(s);
			m_logger->LogInfo("Song Added");
		}
		co_return;
	}
	ICommand MainViewModel::AddCommand()
	{
		if (!m_addCommand)
		{
			m_addCommand = winrt::make<RelayCommand>([this]() -> IAsyncAction
			{
					co_await Helpers::FilePicker::PickAndCopyFileAsync(nullptr, m_songProvider->GetDefaultPath());
					co_await InitializeSongsAsync();
			});
		}
		return m_addCommand;
	}
}
