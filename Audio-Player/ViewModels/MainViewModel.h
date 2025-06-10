#pragma once

#include "MainViewModel.g.h"

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <Models/SongModel.h>
#include <Framework/BindableBase.h>
#include <Framework/Logger.h>
#include <Framework/SongProvider.h>

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Microsoft::UI::Xaml::Input;

using namespace winrt::Audio_Player::Framework;
using namespace winrt::Audio_Player;

namespace winrt::Audio_Player::implementation
{
    struct MainViewModel : MainViewModelT<MainViewModel, BindableBase>
    {
        MainViewModel();

        void Inject(std::shared_ptr<ILogger> logger, std::shared_ptr<ISongProvider> provider);

        IObservableVector<Audio_Player::SongModel> Songs();
        void Songs(IObservableVector<Audio_Player::SongModel> const& value);

        Audio_Player::SongModel SelectedSong();
        void SelectedSong(Audio_Player::SongModel const& value);


        ICommand AddCommand();
        ICommand DeleteCommand();

    private:

        IObservableVector<Audio_Player::SongModel> m_songs = single_threaded_observable_vector<Audio_Player::SongModel>();
        Audio_Player::SongModel m_selectedSong{ nullptr };
        
        std::shared_ptr<ISongProvider> m_songProvider;
        std::shared_ptr<ILogger> m_logger{ nullptr };

        ICommand m_addCommand{ nullptr };
        ICommand m_deleteCommand{ nullptr };
        IAsyncAction InitializeSongsAsync();

    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct MainViewModel : MainViewModelT < MainViewModel, implementation::MainViewModel>
    {
    };
}
