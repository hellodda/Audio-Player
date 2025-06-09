#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif



using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

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

