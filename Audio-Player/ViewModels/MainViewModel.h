#pragma once

#include "MainViewModel.g.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Models/SongModel.h>
#include <Framework/BindableBase.h>
#include <Framework/Logger.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Audio_Player::implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel, Framework::BindableBase>
    {
        MainViewModel();

        void Inject(std::shared_ptr<Framework::ILogger> logger);

        IObservableVector<winrt::Audio_Player::SongModel> Songs();
        void Songs(IObservableVector<winrt::Audio_Player::SongModel> const& value);

        Audio_Player::SongModel SelectedSong();
        void SelectedSong(Audio_Player::SongModel const& value);

    private:

        IObservableVector<Audio_Player::SongModel> m_songs = single_threaded_observable_vector<Audio_Player::SongModel>();
        Audio_Player::SongModel m_selectedSong{ nullptr };
        
        std::shared_ptr<Framework::ILogger> m_logger{ nullptr };
    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct MainViewModel : MainViewModelT < MainViewModel, implementation::MainViewModel>
    {
    };
}
