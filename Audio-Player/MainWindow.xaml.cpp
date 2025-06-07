#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "SongModel.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Audio_Player::implementation
{
	void MainWindow::Setup()
	{
		ExtendsContentIntoTitleBar(true);
	}

	winrt::Audio_Player::MainViewModel MainWindow::MainViewModel()
	{
		return winrt::Audio_Player::ViewModels::Locator::MainViewModel();
	}
}

