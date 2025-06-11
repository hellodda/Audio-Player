#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif



using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace winrt::Microsoft::UI::Xaml::Hosting;

namespace winrt::Audio_Player::implementation
{
	void MainWindow::Setup()
	{
		ExtendsContentIntoTitleBar(true);
	}

	void MainWindow::Inject(Audio_Player::MainViewModel const& viewModel, std::shared_ptr<Framework::ILogger> logger)
	{
		m_viewModel = viewModel;
		m_logger = std::move(logger);
	}

	winrt::Audio_Player::MainViewModel MainWindow::MainViewModel()
	{
		return m_viewModel;
	}
}

void winrt::Audio_Player::implementation::MainWindow::SongsView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
{
   
}

void winrt::Audio_Player::implementation::MainWindow::Playerok_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Playerok().MediaPlayer().MediaEnded(
        winrt::auto_revoke,
        [this](auto const&, auto const&)
        {
            auto& viewModel = MainViewModel();
            auto songs = viewModel.Songs();
            auto selected = viewModel.SelectedSong();

            uint32_t index{};
            if (songs.IndexOf(selected, index))
            {
                index = (index + 1) % songs.Size();
                viewModel.SelectedSong(songs.GetAt(index));

                auto player = Playerok().MediaPlayer();
                player.Source(viewModel.SelectedSong().MediaSource());
                player.Play();
            }
        });
}
