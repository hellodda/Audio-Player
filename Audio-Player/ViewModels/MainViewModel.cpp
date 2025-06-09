#include "pch.h"
#include "MainViewModel.h"
#if __has_include("MainViewModel.g.cpp")
#include "MainViewModel.g.cpp"
#endif

namespace winrt::Audio_Player::implementation
{
	MainViewModel::MainViewModel()
	{
		
	}
	void MainViewModel::Inject(std::shared_ptr<Framework::ILogger> logger)
	{
		m_logger = std::move(logger);
		m_logger->LogInfo("Inject from MainViewModel called");
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
}
