#include "pch.h"
#include "MainViewModel.h"
#if __has_include("MainViewModel.g.cpp")
#include "MainViewModel.g.cpp"
#endif

namespace winrt::Audio_Player::implementation
{
	MainViewModel::MainViewModel()
	{
		Initialize();
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
	void MainViewModel::Initialize()
	{
		for (int i = 0; i < 100; i++)
		{
			winrt::Audio_Player::SongModel model;
			model.Title(L"Example Song");
			model.ImagePath(L"C:\\Users\\user\\Downloads\\a52(.jpeg");
			m_songs.Append(model);
		}
	}
}
