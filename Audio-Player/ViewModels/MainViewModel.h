#pragma once

#include "MainViewModel.g.h"
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "Models/SongModel.h"
#include "Framework/BindableBase.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Audio_Player::implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel, Framework::BindableBase>
    {
        MainViewModel();

        IObservableVector<winrt::Audio_Player::SongModel> Songs();
        void Songs(IObservableVector<winrt::Audio_Player::SongModel> const& value);

        Audio_Player::SongModel SelectedSong();
        void SelectedSong(Audio_Player::SongModel const& value);

    private:

        IObservableVector<Audio_Player::SongModel> m_songs = single_threaded_observable_vector<Audio_Player::SongModel>();
        Audio_Player::SongModel m_selectedSong{ nullptr };

        void Initialize();
    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct MainViewModel : MainViewModelT < MainViewModel, implementation::MainViewModel>
    {
    };
}
